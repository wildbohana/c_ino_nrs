/*
Napisati task prekidac() koji proverava stanje prekidača na određenom pinu.
- Ukoliko je prekidač upravo upaljen, startovati odredjenu funkciju bez 
  parametara, a ukoliko je upravo ugašen startovati drugu funkciju.
- Task preko parametra prima pokazivač na strukturu koja u sebi sadrži pin 
  prekidača, njegovo staro stanje, kao i dva pokazivača na funkcije koje 
  treba da se startuju prilikom paljenja/gašenja prekidača.
- Koristeći dati task, omogućiti uvećanje globalnog brojača br na uzlaznoj 
  ivici signala prekidača SW1 na pinu 2. Task startovati na svakih 50ms.
- Koristeći dati task, omogućiti ispis globalnog brojača br na serijski monitor 
  na silaznoj liniji prekidača SW2 na pinu 7 . Task startovati na svakih 50ms.
*/

typedef void funkcija();

typedef struct podaci {
	int sw;
	int staro_stanje;
	funkcija* f1;
	funkcija* f2;
} Podaci;

Podaci p1, p2;
static int brojac = 0;

void uvecaj()
{
	brojac++;
}

void stampaj()
{
	Serial.println(brojac);
}

void prekidac(int id, void* tptr)
{
	Podaci* p = (Podaci*) tptr;

	int novo_stanje = digitalRead(p->sw);

	if (p->staro_stanje == 1 && novo_stanje == 0)
		if (p->f2)
			p->f2();
	else if (p->staro_stanje == 0 && novo_stanje == 1)
		if (p->f1)
			p->f1();
}

void setup()
{
	Serial.begin(9600);

	p1.sw = 2;
	p1.staro_stanje = digitalRead(p1.sw);
	p1.f1 = uvecaj;
	p1.f2 = NULL;
	createTask(prekidac, 50, TASK_ENABLE, &p1);

	p2.sw = 7;
	p2.staro_stanje = digitalRead(p2.sw);
	p2.f1 = NULL;
	p2.f2 = stampaj;
	createTask(prekidac, 50, TASK_ENABLE, &p2);
}

void loop()
{

}
