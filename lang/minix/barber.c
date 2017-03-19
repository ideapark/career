#define CHAIRS  5              /* chairs for waiting customers */

typedef int semaphone;
semaphone customers = 0;       /* customers waiting for barber */
semaphone barbers = 0;         /* barbers waiting for customer */
semaphone mutex = 1;           /* exclude access */
int waiting = 0;               /* customers waiting (not serviced yet) */

void barber(void)
{
	while (1) {
		down(customers);       /* if customers is 0, sleeping */
		down(mutex);           /* ask process wait */
		waiting = waiting - 1; /* waiting customer minus 1 */
		up(barbers);           /* baber starting cutting hair */
		up(mutex);             /* release waiting */
		cut_hair();            /* cut hair (non-critical area) */
	}
}

void customers(void)
{
	down(mutex);               /* enter critical area */
	if (waiting < CHAIRS) {
		waiting = waiting + 1; /* waiting customer add 1 */
		up(customers);         /* wakeup barber */
		up(mutex);             /* release waiting access */
		down(barbers);         /* if barbers is 0, sleeping */
		get_haircut();         /* sit down waiting for service */
	} else {
		up(mutex);             /* customer leaving */
	}
}
