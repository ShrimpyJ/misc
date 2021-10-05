#include <stdio.h>
#include <stdlib.h>

#define SPEED_LIMIT    40
#define YELLOW          5

struct tlight
{
	double green, red;
} Tlight;

double hour_to_min(double hour)
{
	return hour*60*60;
}

double calc_time(double distance, int speed)
{
	return hour_to_min(distance/speed) + YELLOW;
}

int main(int argc, char *argv)
{
	struct tlight *tl;

	tl = malloc(sizeof(struct tlight*));

	tl->green = calc_time(1.00, SPEED_LIMIT);
	printf("%.0lf\n", tl->green);

	return 0;
}
