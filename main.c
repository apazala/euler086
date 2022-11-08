#include <stdio.h>
#include <inttypes.h>

//Pitagoras triplets
typedef struct {
	int a;
	int b;
	int c;
} triplet;

struct {
	triplet stack[1000000];
	int front;
} stack;

#define init(s) ((s).front = -1)
#define isempty(s) ((s).front == -1)
#define any(s) ((s).front != -1)
#define push(s, x) ((s).stack[++((s).front)] = (x))
#define pop(s) ((s).stack[(s).front--])
#define top(s) ((s).stack[(s).front])

#define MAXM 400001
int64_t solutions[5000000];

void accounttriplet(triplet t) {
	for (int a = t.a, b = t.b, c = t.c; a < 2 * MAXM && b < 2 * MAXM; a += t.a, b += t.b, c += t.c) {
		int low = (b + 1) >> 1; //ceil(b/2)
		int high = (b > a ? a : b - 1);
		if (high >= low)
			solutions[a] += high - low + 1;
		low = (a + 1) >> 1; //ceil(a/2)
		high = (a > b ? b : a - 1);
		if (high >= low)
			solutions[b] += high - low + 1;
	}
}

void iteratepittriplets() {

	init(stack);

	triplet t1 = { 3, 4, 5 };

	push(stack, t1);
	while (any(stack)) {
		triplet t2 = pop(stack);
		if (t2.a >= 2 * MAXM || t2.b >= 2 * MAXM) continue;

		accounttriplet(t2);

		//variant 1
		t1.a = t2.a - 2 * t2.b + 2 * t2.c;
		t1.b = 2 * t2.a - t2.b + 2 * t2.c;
		t1.c = 2 * t2.a - 2 * t2.b + 3 * t2.c;

		push(stack, t1);

		//variant 2
		t1.a = t2.a + 2 * t2.b + 2 * t2.c;
		t1.b = 2 * t2.a + t2.b + 2 * t2.c;
		t1.c = 2 * t2.a + 2 * t2.b + 3 * t2.c;

		push(stack, t1);

		//variant 3
		t1.a = -t2.a + 2 * t2.b + 2 * t2.c;
		t1.b = -2 * t2.a + t2.b + 2 * t2.c;
		t1.c = -2 * t2.a + 2 * t2.b + 3 * t2.c;

		push(stack, t1);

	}

}

int main()
{
	iteratepittriplets();


	for (int i = 1; i < MAXM; i++) {
		solutions[i] += solutions[i - 1];
		if (solutions[i] > 1000000) {
			printf("%d\n", i);
			break;
		}
	}

	return 0;
}