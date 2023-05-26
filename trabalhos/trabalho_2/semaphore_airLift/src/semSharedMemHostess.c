/**
 *  \file semSharedMemHostess.c (implementation file)
 *
 *  \brief Problem name: Air Lift.
 *
 *  Synchronization based on semaphores and shared memory.
 *  Implementation with SVIPC.
 *
 *  Definition of the operations carried out by the hostess:
 *     \li waitForNextFlight
 *     \li waitForPassenger
 *     \li checkPassport
 *     \li signalReadyToFlight
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

/** \brief hostess waits for next flight */
static void waitForNextFlight ();

/** \brief hostess waits for passenger */
static void waitForPassenger();

/** \brief hostess checks passport */
static bool checkPassport ();

/** \brief hostess signals boarding is complete */
static void signalReadyToFlight ();


/** \brief getter for number of passengers flying */
static int nPassengersInFlight ();

/** \brief getter for number of passengers waiting */
static int nPassengersInQueue ();

/**
 *  \brief Main program.
 *
 *  Its role is to generate the life cycle of one of intervening entities in the problem: the hostess.
 */

int main (int argc, char *argv[])
{
    int key;                                                           /*access key to shared memory and semaphore set */
    char *tinp;                                                                      /* numerical parameters test flag */

    /* validation of command line parameters */

    if (argc != 4) { 
        freopen ("error_HT", "a", stderr);
        fprintf (stderr, "Number of parameters is incorrect!\n");
        return EXIT_FAILURE;
    }
    else freopen (argv[3], "w", stderr);

    strcpy (nFic, argv[1]);
    key = (unsigned int) strtol (argv[2], &tinp, 0);
    if (*tinp != '\0')
    { fprintf (stderr, "Error on the access key communication!\n");
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

    /* simulation of the life cycle of the hostess */

    int nPassengers=0;
    bool lastPassengerInFlight;

    while(nPassengers < N ) {
        waitForNextFlight();
        do { 
            waitForPassenger();
            lastPassengerInFlight = checkPassport();
            nPassengers++;
        } while (!lastPassengerInFlight);
        signalReadyToFlight();
    }

    /* unmapping the shared region off the process address space */

    if (shmemDettach (sh) == -1) {
        perror ("error on unmapping the shared region off the process address space");
        return EXIT_FAILURE;;
    }

    return EXIT_SUCCESS;
}

/**
 *  \brief wait for Next Flight.
 *
 *  Hostess updates its state and waits for plane to be ready for boarding
 *  The internal state should be saved.
 *
 */

static void waitForNextFlight ()
{
    if (semDown (semgid, sh->mutex) == -1)  {                                                  /* enter critical region */
        perror ("error on the up operation for semaphore access (HT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    sh->fSt.st.hostessStat = WAIT_FOR_FLIGHT;							//muda para a espera do voo
    saveState(nFic, &sh->fSt);								//fazer save
       
    //
    
    if (semUp (semgid, sh->mutex) == -1)                                                   /* exit critical region */
    { perror ("error on the down operation for semaphore access (HT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    if (semDown(semgid, sh->readyForBoarding) == -1){					//faz se down ao semaforo do ready for boarding para esperar que o piloto deixe entrar
    	perror ("error on the down operation hostess waitForNextFlight");
    	exit (EXIT_FAILURE);
    }
    //
}

/**
 *  \brief hostess waits for passenger
 *
 *  hostess waits for passengers to arrive at airport.
 *  The internal state should be saved.
 */

static void waitForPassenger ()
{
    if (semDown (semgid, sh->mutex) == -1)                                                      /* enter critical region */
    { perror ("error on the up operation for semaphore access (HT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */    
    sh->fSt.st.hostessStat = WAIT_FOR_PASSENGER; 						//passa a dizer que esta a espera
    saveState(nFic, &sh->fSt);								//guardar o estado   
    //

    if (semUp (semgid, sh->mutex) == -1) {                                                  /* exit critical region */
     perror ("error on the down operation for semaphore access (HT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    if (semDown(semgid,sh->passengersInQueue) == -1) {                 			// fazer down ao semaforo para esperar que haja alguem na fila que lhe faca o up
	perror ("error down for passenger_In_Queue");
	exit (EXIT_FAILURE);
    }
    //
}

/**
 *  \brief passport check
 *
 *  The hostess checks passenger passport and waits for passenger to show id
 *  The internal state should be saved twice.
 *
 *  \return should be true if this is the last passenger for this flight
 *    that is: 
 *      - flight is at its maximum capacity 
 *      - flight is at or higher than minimum capacity and no passenger waiting 
 *      - no more passengers
 */

static bool checkPassport()
{
    bool last;

    /* insert your code here */
    if ( semUp(semgid,sh->passengersWaitInQueue) == -1) {                 				//fazer down esperar pelo id do passageiro
        perror ("error up for hostess - checkPassaport");
        exit (EXIT_FAILURE);
    }

    //

    if (semDown (semgid, sh->mutex) == -1) {                                                     /* enter critical region */
        perror ("error on the up operation for semaphore access (HT)");
        exit (EXIT_FAILURE);

    }

    /* insert your code here */
    sh->fSt.st.hostessStat = CHECK_PASSPORT;
    saveState(nFic, &sh->fSt);
    
    //

    if (semUp (semgid, sh->mutex) == -1)     {                                                 /* exit critical region */
        perror ("error on the up operation for semaphore access (HT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    if ( semDown(semgid,sh->idShown) == -1) {                 				//fazer down esperar pelo id do passageiro
        perror ("error down for hostess - checkPassaport");
        exit (EXIT_FAILURE);
    }								
    //

    if (semDown (semgid, sh->mutex) == -1)  {                                                 /* enter critical region */
        perror ("error on the up operation for semaphore access (HT)");
        exit (EXIT_FAILURE);

    }

    /* insert your code here */
    
    savePassengerChecked(nFic, &sh->fSt);
    sh->fSt.nPassInQueue--;									// a hostess e que retira a fila
    sh->fSt.nPassInFlight++;									//ao mesmo tempo no voo aumenta o numero de passageiros
    sh->fSt.totalPassBoarded++;								//dar update ao numero de passageiros que ja entraram
    saveState(nFic, &sh->fSt);
    //

    if (semUp (semgid, sh->mutex) == -1) {                                                     /* exit critical region */
        perror ("error on the up operation for semaphore access (HT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    last = false;
    if( nPassengersInFlight() == MAXFC){							//se ja estiver cheio entao segue
    	last = true;						
    }
    else if( nPassengersInQueue() == 0){							//se nao houver ninguem na fila
    	if( (nPassengersInFlight() > MINFC) ){		//e ja tiver o minimo entao segue ou se ja estiverem todos os passageiros
    		last = true;
    	}
    	if(sh->fSt.totalPassBoarded == N){
    		last=true;
    		sh->fSt.finished = true;
    	}
    }
    //

    return last;
}

static int nPassengersInFlight()
{
    return sh->fSt.nPassInFlight;
}

static int nPassengersInQueue()
{
    return sh->fSt.nPassInQueue;
}

/**
 *  \brief signal ready to flight 
 *
 *  The flight is ready to go.
 *  The hostess updates her state, registers the number of passengers in this flight 
 *  and checks if the airlift is finished (all passengers have boarded).
 *  Hostess informs pilot that plane is ready to flight.
 *  The internal state should be saved.
 */
void  signalReadyToFlight()
{
    if (semDown (semgid, sh->mutex) == -1) {                                                /* enter critical region */
        perror ("error on the up operation for semaphore access (HT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    
    sh->fSt.st.hostessStat = READY_TO_FLIGHT;							// muda o seu estado para esta pronta
    sh->fSt.nPassengersInFlight[sh->fSt.nFlight-1] = sh->fSt.nPassInFlight;				//registar o numero de passageiros
    saveState(nFic, &sh->fSt);
    saveFlightDeparted(nFic, &sh->fSt);
    //

    if (semUp (semgid, sh->mutex) == -1) {                                                     /* exit critical region */
        perror ("error on the up operation for semaphore access (HT)");
        exit (EXIT_FAILURE);
    }

    /* insert your code here */
    if (semUp(semgid, sh->readyToFlight) == -1){						//faz se up ao semaforo do ready to flight, ja esta toda a gente o voo pode levantar
    	perror ("error on the up hostess readyToFlight");
    	exit (EXIT_FAILURE);
    }
    //
}


