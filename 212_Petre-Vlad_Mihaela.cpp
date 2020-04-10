#include <iostream>
#include <stdlib.h>

using namespace std;

class Nod
{
protected:
    int info;
    Nod* next;
    static int n;

public:
    Nod (int, Nod*); ///constructor de initializare
    Nod (Nod&); ///constructor de copiere
    Nod& operator=(Nod &nod);
    virtual ~Nod(); ///destructor virtual
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream& operator>>(istream&, Nod&);
    friend ostream& operator<<(ostream&, Nod&);
    static void nrNoduri(){cout<<n<<"\n";}
    friend class Nod_dublu;
    friend class LSI;
};

///destructor
Nod::~Nod(){}

///constructor de initializare
int Nod::n;
Nod::Nod (int inf=0, Nod* urm=NULL)
{
    n++;
    info=inf;
    next=urm;
}

///constructor de copiere
Nod::Nod(Nod &nod1)
{
    n++;
    info=nod1.info;
    next=nod1.next;
}

Nod& Nod::operator=(Nod &nod)
{
    n++;
    info=nod.info;
    next=nod.next;
}

istream& operator>>(istream& in,Nod& nod)
{
    nod.citire(in);
    return in;
}

void Nod::citire(istream &in)
{
    cout<<"Cititi info nod = ";
    in>>info;
    cout<<"\n";
    next=NULL;
}

ostream& operator<<(ostream& out, Nod& nod)
{
    nod.afisare(out);
    return out;
}

void Nod::afisare(ostream &out)
{
    out<<"Info nod = "<<info<<"\n";
    out<<"Urmatorul nod : ";
    if(next==NULL)
        out<<" - \n";
    else
        out<<next->info<<"\n";
}

///derivata clasei Nod
class Nod_dublu : public Nod
{
private:
    Nod * ante;
public:
    Nod_dublu(int, Nod*, Nod*); ///constructor de initializare
    Nod_dublu (Nod_dublu&); ///constructor de copiere
    Nod_dublu& operator=(Nod_dublu &nod);
    ~Nod_dublu(); ///destructor
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream&, Nod_dublu&);
    friend ostream& operator<<(ostream&, Nod_dublu&);
    friend class LDI;
    friend void insertion_sort(Nod_dublu *);
    friend class LSI;
};
///destructor
Nod_dublu::~Nod_dublu(){}

/// constructor de initializare
Nod_dublu::Nod_dublu(int inf=0,Nod* pre=NULL, Nod* urm=NULL):Nod(inf,urm)
{
    ante=pre;
}

///constructor de copiere
Nod_dublu::Nod_dublu(Nod_dublu &nd1)
{
    info=nd1.info;
    next=nd1.next;
    ante=nd1.ante;
}

Nod_dublu& Nod_dublu::operator=(Nod_dublu &nd)
{
    n++;
    info=nd.info;
    next=nd.next;
    ante=nd.ante;
}

istream& operator>>(istream& in, Nod_dublu& nd)
{
    nd.citire(in);
    return in;
}

void Nod_dublu::citire(istream &in)
{
    Nod::citire(in);
    ante=NULL;
}

ostream& operator<<(ostream& out, Nod_dublu& nd)
{
    nd.afisare(out);
    return out;
}

void Nod_dublu::afisare(ostream &out)
{
    Nod::afisare(out);
    cout<<"Nodul anterior : ";
    if(ante==NULL)
        out<<" - \n";
    else
        out<<ante->info<<"\n";
}


class LDI
{
protected:
    Nod_dublu *prim, *ultim;
    static int nr_l;
public:
    LDI(int,int,Nod_dublu*); ///constructor de initializare
    LDI(LDI&); ///constructor de copiere
    virtual ~LDI(); ///destructor virtual
    LDI& operator=(LDI &L);
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream& operator>>(istream&, LDI&);
    friend ostream& operator<<(ostream&, LDI&);
    friend void insertion_sort(Nod_dublu *);
    friend Nod_dublu* primul_nod(LDI&);
    static void nrListe(){cout<<nr_l<<"\n";}
};

Nod_dublu* primul_nod(LDI &L)
{
    return L.prim;
}

///destructor
LDI::~LDI(){}

int LDI::nr_l;
/// constructor de initializare
LDI::LDI(int nr_noduri=1, int init=0, Nod_dublu *p=new Nod_dublu)
{
    nr_l++;
    prim=ultim=p;
    Nod_dublu *nd;

    for(int i=1;i<nr_noduri;i++)
    {
        nd=new Nod_dublu;
        nd->info=init;
        nd->next=NULL;
        nd->ante=ultim;
        ultim->next=nd;
        ultim=nd;
    }
}

///constructor de copiere
LDI::LDI(LDI &L)
{
    nr_l++;
    prim=L.prim;
    ultim=L.ultim;
}

LDI& LDI::operator=(LDI &L)
{
    nr_l++;
    prim=L.prim;
    ultim=L.ultim;
}

istream& operator>>(istream& in, LDI& L)
{
    L.citire(in);
    return in;
}

void LDI::citire(istream &in)
{
    cout<<"Cititi nr. de noduri din lista: ";
    int nr; in>>nr;
    while(nr<=0)
    {
        cout<<"Dati un nr. pozitiv nenul.\n";
        cout<<"Cititi nr. de noduri din lista: ";
        in>>nr;
    }
    int v[nr];
    cout<<"Dati elementele listei (nr. intregi) : ";
    for(int i=0;i<nr;i++)
    {
        in>>v[i];
    }
    prim->info=v[0];
    ultim->info=v[0];
    Nod_dublu *nd;
    for(int i=1;i<nr;i++)
    {
        nd=new Nod_dublu;
        nd->info=v[i];
        nd->next=NULL;
        nd->ante=ultim;
        ultim->next=nd;
        ultim=nd;
    }
}

ostream& operator<<(ostream& out, LDI& L)
{
    L.afisare(out);
    return out;
}

void LDI::afisare(ostream &out)
{
    for(Nod_dublu *p=prim; p!=NULL; p=(Nod_dublu*)p->next)
        out<<p->info<<" ";
    out<<"\n";
}

///derivata clasei LDI
class LSI : public LDI
{
private:
    Nod *pr = (Nod*)prim;
    Nod *ul = (Nod*)ultim;

public:
    LSI(int,int,Nod*); ///constructor de initializare
    LSI(LSI&); ///constructor de copiere
    ~LSI(); ///destructor
    LSI& operator=(LSI &L);
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream&, LDI&);
    friend ostream& operator<<(ostream&, LDI&);
};
///destructor
LSI::~LSI(){}

/// constructor de initializare
LSI::LSI(int nr_noduri=1, int init=0, Nod *p=new Nod):LDI(nr_noduri,init,(Nod_dublu*)p)
{
    Nod *nod = pr->next;
    for(int i=1;i<nr_noduri;i++)
    {
        ((Nod_dublu*)nod)->ante=NULL;
        nod=nod->next;
    }
}

///constructor de copiere
LSI::LSI(LSI &L)
{
    pr=L.pr;
    ul=L.ul;
}

LSI& LSI::operator=(LSI &L)
{
    pr=L.pr;
    ul=L.ul;
}

ostream& operator<<(ostream& out, LSI& L)
{
    L.afisare(out);
    return out;
}

void LSI::afisare(ostream &out)
{
    LDI::afisare(out);
}

istream& operator>>(istream& in, LSI& L)
{
    L.citire(in);
    return in;
}

void LSI::citire(istream &in)
{
    LDI::citire(in);
    for(Nod *nod = pr->next; nod!=NULL; nod=nod->next)
        ((Nod_dublu*)nod)->ante=NULL;
}

void insertion_sort(Nod_dublu *cap)
{
    int pas=1;
    LDI sortat; sortat.prim=NULL;

    Nod_dublu *curent1 = cap;
    Nod_dublu *urmeaza;

    while (curent1 != NULL)
    {
        urmeaza = (Nod_dublu*)curent1->next;
        curent1->ante = curent1->next = NULL;;
        Nod_dublu* de_sortat = curent1;
        Nod_dublu* curent;

        if (sortat.prim == NULL)
            sortat.prim = de_sortat;

        else if (sortat.prim->info >= de_sortat->info)
        {
            de_sortat->next = sortat.prim;
            ((Nod_dublu*)de_sortat->next)->ante = de_sortat;
            sortat.prim = de_sortat;
        }
        else
        {
            curent = sortat.prim;

            while (curent->next != NULL &&  ((Nod_dublu*)curent->next)->info < de_sortat->info)
                curent = (Nod_dublu*)curent->next;

            de_sortat->next = curent->next;

            if (curent->next != NULL)
                ((Nod_dublu*)de_sortat->next)->ante = de_sortat;

            curent->next = de_sortat;
            de_sortat->ante = curent;
        }

        curent1 = urmeaza;

        cout<<"Pas "<<pas<<": "<<sortat;
        pas++;
    }
    cout<<"Lista sortata este:"<<sortat;
}

void menu_output()
{
    cout<<"\n Petre-Vlad Mihaela - Grupa 212 - Proiect 2 - Tema 1\n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"Optiuni:\n\n";
    cout<<"1. Citirea a n LDI\n";
    cout<<"2. Sortarea prin insertie directa\n";
    cout<<"3. Nr. de liste create\n";
    cout<<"4. Test upcasting\n";
    cout<<"5. Test downcasting\n";
    cout<<"6. Stergeti consola\n";
    cout<<"0. Iesire\n";
}

void menu()
{
    int option=0, afis=0, nl=0, i;
    LDI *L;

    do
    {
        if(afis==0)
        {
            menu_output();
            afis=1;
        }

        cout<<"\n\nIntroduceti numarul actiunii: ";
        cin>>option;

        if(option==1)
        {
            cout<<"\nNr. de LDI = ";cin>>nl;
            while(nl<=0)
            {
                cout<<"\nDati un numar pozitiv nenul.\n";
                cout<<"\nNr. LDI = ";cin>>nl;
            }

            L=new LDI[nl];
            for(i=0;i<nl;i++)
            {
                cout<<"\nCititi lista "<<i+1<<"\n";
                cin>>L[i];
            }

            cout<<"\nAti introdus urmatoarele LDI:\n";
            for(i=0;i<nl;i++)
                cout<<L[i];
        }

        if(option==2)
        {
            if(nl==0)
                cout<<"\nNu ati dat listele!\n";

            else if(nl==1)
            {
                cout<<"\nSortarea listei date\n";
                Nod_dublu* p=primul_nod(L[0]);
                insertion_sort(p);
            }
            else
            {
                int r;
                cout<<"Vreti sa sortati toate listele? Tastati 1(da) sau 0(nu):"; cin>>r;
                if(r==1)
                {
                    for(i=0;i<nl;i++)
                    {
                        cout<<"\nSortarea listei "<<i+1<<"\n";
                        Nod_dublu* p=primul_nod(L[i]);
                        insertion_sort(p);
                    }
                }
                else if(r==0)
                {
                    int s[nl], c; i=0;
                    cout<<"\nDati nr. listelor de sortat, tastati 0 pt. a va opri: ";
                    do
                    {
                        cin>>c;
                        if(c>nl || c<0)
                        {
                            do
                            {
                                cout<<"Nr. invalid! Dati un nr. corespunzator: ";
                                cin>>c;
                            }
                            while(c>nl || c<0);
                        }
                        s[i]=c; i++;
                    }
                    while(c!=0);

                    for(int j=0;j<i-1;j++)
                    {
                        cout<<"\nSortarea listei "<<s[j]<<"\n";
                        Nod_dublu* p=primul_nod(L[s[j]-1]);
                        insertion_sort(p);
                    }
                }
                else cout<<"Raspuns invalid\n";
            }
        }

        if(option==3)
        {
            cout<<"Nr. de liste create in timpul rularii acestui program pana acum este ";
            LDI::nrListe();
        }

        if(option==4)///upcasting
        {
            Nod *u=new Nod_dublu;
            cin>>*u;
            cout<<*u;
        }

        if(option==5)///downcasting
        {
            Nod_dublu *d=(Nod_dublu*)new Nod;
            cin>>*d;
            cout<<*d;
        }

        if(option==6)
        {
            system("cls"); ///Sterge continutul curent al consolei
            afis=0;
        }

        if (option==0)
        {
            cout<<"\nEXIT!\n";
        }

        if (option<0||option>6)
        {
            cout<<"\nSelectie invalida\n";
        }
    }
    while(option!=0);
}

int main()
{
    menu();

    return 0;
}
