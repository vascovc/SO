/**
 *  \file semSharedMemPilot.c (implementation file)
 *
 *  \brief Problem name: Air Lift
 *
 *  Synchronization based on semaphores and shared memory.
 *  Implementation with SVIPC.
 *
 *  Definition of the operations carried out by the pilot:
 *     \li flight
 *     \li signalReadyForBoarding
 *     \li waitUntilReadyToFlight
 *     \li dropPassengersAtTarget
 *
 *  \author Nuno Lau - January 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <sys/time.h>
#include <errno.h>

#include "probConst.h"
#include "probDataStruct.h"
#include "logging.h"
#include "sharedDataSync.h"
#include "semaphore.h"
#include "sharedMemory.h"


/** \brief logging file name */
static char nFic[51];

/** \brief shared memory block access identifier */
static int shmid;

/** \brief semaphore set access identifier */
static int semgid;

/** \brief pointer to shared memory region */
static SHARED_DATA *sh;

static void flight (bool go);
static void signalReadyForBoarding ();
static void waitUntilReadyToFlight ();
static void dropPassengersAtTarget ();
static bool isFinished ();

/**
 *  \brief Main program.
 *
 *  Its role is to generate the life cycle of one of intervening entities in the problem: the pilot.
 */

int main (int argc, char *argv[])
{
    int key;                                                           /*access key to shared memory and semaphore set */
    char *tinp;                                                                      /* numerical parameters test flag */

    /* validation of command line parameters */

    if (argc != 4) { 
        freopen ("error_PT", "a", stderr);
        fprintf (stderr, "Number of parameters is incorrect!\n");
        return EXIT_FAILURE;
    }
    else freopen (argv[3], "w", stderr);
    strcpy (nFic, argv[1]);
    key = (unsigned int) strtol (argv[2], &tinp, 0);
    if (*tinp != '\0') {
        fprintf (stderr, "Error on the access key communication!\n");
        return EXIT_FAILURE;
    }

    /* connection to the semaphore set and the shared memory region and mapping the shared region onto the
       process address space */

    if ((semgid = semConnect (key)) == -1) { 
        perror ("error on connecting to the semaphore set");
        return EXIT_FAILURE;
    }
    if ((shmid = shmemConnect (key)) == -1) { 
        perror ("error on connecting to the shared memory region");
        return EXIT_FAILURE;
    }
    if (shmemAttach (shmid, (void **) &sh) == -1) { 
        perror ("error on mapping the shared region on the process address space");
        return EXIT_FAILURE;
    }

    srandom ((unsigned int) getpid ());                                                 /* initialize random generator */

    /* simulation of the life cycle of the pilot */

    while(!isFinished()) {
        flight(false); // from target to origin
        signalReadyForBoarding();
        waitUntilReadyToFlight();
        flight(true); // from origin to target
        dropPassengersAtTarget();
    }

    /* unmapping the shared region off the process address space */

    if (shmemDettach (sh) == -1) { 
        perror ("error on unmapping the shared region off the process address space");
        return EXIT_FAILURE;;
    }

    return EXIT_SUCCESS;
}

/**
 *  \brief test if air lift finished
 */
static bool isFinished ()
{
    return sh->fSt.finished;
}

/**
 *  \brief flight.
 *
 *  The pilot takes passenger to destination (go) or 
 *  plane back to starting airport (return)
 *  state should be saved.
 *
 *  \param go true if going to destination
 */

static void flight (bool go)
{
    if (semDown (semgid, sh->mutex) == -1) {                                                      /* enter critical region */
        perror ("error on the up operation for semaphore access (PT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    
    if(go){											//altera se o estado consoante se esta a ir ou a vir
    	sh->fSt.st.pilotStat = FLYING;
    }
    else{
    	sh->fSt.st.pilotStat = FLYING_BACK;							//altera se o estado para a retornar
							
    }
    saveState(nFic, &sh->fSt);								//fazer save
    //

    if (semUp (semgid, sh->mutex) == -1) {                                                      /* exit critical region */
        perror ("error on the up operation for semaphore access (PT)");
        exit (EXIT_FAILURE);
    }

    usleep((unsigned int) floor ((MAXFLIGHT * random ()) / RAND_MAX + 100.0));
}

/**
 *  \brief pilot informs hostess that plane is ready for boarding
 *
 *  The pilot updates its state and signals the hostess that boarding may start
 *  The flight number should be updated.
 *  The internal state should be saved.
 */

static void signalReadyForBoarding ()
{
    if (semDown (semgid, sh->mutex) == -1) {                                                      /* enter critical region */
        perror ("error on the up operation for semaphore access (PT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    sh->fSt.st.pilotStat = READY_FOR_BOARDING;						//passa a estar a espera
    sh->fSt.nFlight++;										//aumentar o numero do voo
    saveState(nFic, &sh->fSt);								//dar save
    //

    if (semUp (semgid, sh->mutex) == -1) {                                                      /* exit critical region */
        perror ("error on the up operation for semaphore access (PT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    if (semUp(semgid, sh->readyForBoarding) == -1){						//faz se up ao semaforo do ready for boarding para a hostess continuar
    	perror ("error on the up operation piloto signalForBoarding");
    	exit (EXIT_FAILURE);
    }
    //

}

/**
 *  \brief pilot waits for plane to get filled with passengers.
 *
 *  The pilot updates its state and wait for Boarding to finish 
 *  The internal state should be saved.
 */

static void waitUntilReadyToFlight ()
{
    if (semDown (semgid, sh->mutex) == -1) {                                                      /* enter critical region */
        perror ("error on the up operation for semaphore access (PT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    sh->fSt.st.pilotStat = WAITING_FOR_BOARDING;						//o piloto passa a estar a espera
    saveStartBoarding(nFic, &sh->fSt);							//fazer savem, tem que ser este
    saveState(nFic, &sh->fSt); //para dar igual ao do prof, faz a linha em branco para separar da hostess							
    //

    if (semUp (semgid, sh->mutex) == -1) {                                                      /* exit critical region */
        perror ("error on the up operation for semaphore access (PT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    if (semDown(semgid, sh->readyToFlight) == -1){						//faz se down ao semaforo do ready to flight, tem que esperar que os passageiros subam
    	perror ("error on the down piloto readyToFlight");
    	exit (EXIT_FAILURE);
    }
    //
}

/**
 *  \brief pilot drops passengers at destination.
 *
 *  Pilot update its state and allows passengers to leave plane
 *  Pilot must wait for all passengers to leave plane before starting to return.
 *  The internal state should not be saved twice (after allowing passengeres to leave and after the plane is empty).
 */

static void dropPassengersAtTarget ()
{
    if (semDown (semgid, sh->mutex) == -1) {                                                  /* enter critical region */
        perror ("error on the down operation for semaphore access (PT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    sh->fSt.st.pilotStat = DROPING_PASSENGERS;
    saveFlightArrived(nFic, &sh->fSt);							//guardar o estado, parece ser este
    saveState(nFic, &sh->fSt); //para dar igual ao do prof, faz a linha em branco com todos no aviao ainda
    //

    if (semUp (semgid, sh->mutex) == -1)  {                                                   /* exit critical region */
        perror ("error on the up operation for semaphore access (PT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    
    // a ordem pode importar ter isso em atencao por causa de deadlock mas parece me que deve ser assim
    //a operacao de leitura devia ser feita dentro da RC mas nao deve de causar nada
    for(int n_passengers = 0;n_passengers < sh->fSt.nPassengersInFlight[sh->fSt.nFlight-1] ; n_passengers++){
	    if( semUp(semgid, sh->passengersWaitInFlight) == -1){
	    	perror ("error on the up piloto - deixar passageiros");			//para deixar os passageiros sair,  tem que ser um ciclo para subir todos os semaforos para os passageiros
            exit (EXIT_FAILURE);									
	    }
    }
    if(semDown(semgid, sh->planeEmpty) == -1){
    	perror ("error on the down piloto - aviao vazio");					//esperar que o aviao fique vazio
        exit (EXIT_FAILURE);									
    }
    //

    if (semDown (semgid, sh->mutex) == -1) {                                                  /* enter critical region */
        perror ("error on the down operation for semaphore access (PT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    
    saveFlightReturning(nFic, &sh->fSt);							//guardar o estado, voo de retorno
    
    //

    if (semUp (semgid, sh->mutex) == -1)  {                                                   /* exit critical region */
        perror ("error on the up operation for semaphore access (PT)");
        exit (EXIT_FAILURE);
    }
}

