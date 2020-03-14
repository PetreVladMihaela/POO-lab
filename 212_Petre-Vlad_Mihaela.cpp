#include <iostream>
#include <cstdlib>

using namespace std;

class Vector
{
private:
    double *vect;
    int nr;

public:
    Vector(double,int);
    Vector (Vector&);
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Vector& v);
    friend ostream& operator<<(ostream &out, Vector& v);
    Vector& operator=(Vector &v);
    friend void reactualizare(Vector& v, double n_nou, int nr_nou);
    friend void operator+=(Vector& v1, Vector& v2);
    friend void operator-=(Vector& v1, Vector& v2);
    friend Vector& operator+(Vector& v1, Vector& v2);
    friend Vector& operator-(Vector& v1, Vector& v2);
    friend bool operator==(Vector& v1, Vector& v2);
    friend bool operator!=(Vector& v1, Vector& v2);
    friend int length(Vector& v);
    friend double elem(Vector& v, int i);
    ~Vector();
};

///destructor
Vector::~Vector()
{
    delete []vect;

};

///constr pt initializare
Vector::Vector(double n1=0,int nr1=1)
{
    nr=nr1;
    vect=new double[nr1];
    for(int i=0;i<nr1;i++)
        vect[i]=n1;
}

///constr pt copiere
Vector::Vector(Vector &v)
{
    nr=v.nr;
    vect=new double[nr];
    for(int i=0;i<nr;i++)
        vect[i]=v.vect[i];
}

void Vector::citire(istream &in)
{
    cout<<"Cititi nr. de elem.: ";
    in>>nr;
    while(nr<=0)
    {
        cout<<"Dati un nr. pozitiv nenul.\n";
        cout<<"Cititi nr. de elem.: ";
        in>>nr;
    }
    double el;
    vect=new double[nr];
    cout<<"Cititi elem.: ";
    for(int i=0;i<nr;i++)
    {
        in>>el;
        vect[i]=el;
    }
}

void Vector::afisare(ostream &out)
{
    for(int i=0;i<nr;i++)
        out<<vect[i]<<" ";
        out<<"\n";
}

istream& operator>>(istream& in,Vector& v)
{
    v.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Vector& v)
{
    v.afisare(out);
    return out;
}

Vector& Vector::operator=(Vector &v)
{
    nr=v.nr;
    vect=new double[nr];
    for(int i=0;i<nr;i++)
        vect[i]=v.vect[i];
}

void reactualizare(Vector& v, double n_nou, int nr_nou)
{
    v.nr=nr_nou;
    v.vect=new double[nr_nou];
    for(int i=0;i<nr_nou;i++)
        v.vect[i]=n_nou;
}

inline void operator+=(Vector& v1, Vector& v2)
{
    if(v1.nr!=v2.nr)
    {
        cout<<"Eroare: vectorii nu au aceeasi dimensiune!\n";
        exit(EXIT_FAILURE);
    }

    else
    {
        for(int i=0;i<v1.nr;i++)
            v1.vect[i]=v1.vect[i]+v2.vect[i];
    }
}

inline void operator-=(Vector& v1, Vector& v2)
{
    if(v1.nr!=v2.nr)
    {
        cout<<"Eroare: vectorii nu au aceeasi dimensiune!\n";
        exit(EXIT_FAILURE);
    }

    else
    {
        for(int i=0;i<v1.nr;i++)
            v1.vect[i]=v1.vect[i]-v2.vect[i];
    }
}

inline Vector& operator+(Vector &v1, Vector& v2)
{
    if(v1.nr!=v2.nr)
    {
        cout<<"Eroare: vectorii nu au aceeasi dimensiune!\n";
        exit(EXIT_FAILURE);
    }

    else
    {
        Vector *v=new Vector(0,v1.nr);
        for(int i=0;i<v1.nr;i++)
            v->vect[i]=v1.vect[i]+v2.vect[i];
            return *v;
    }
}

inline Vector& operator-(Vector &v1, Vector& v2)
{
    if(v1.nr!=v2.nr)
    {
        cout<<"Eroare: vectorii nu au aceeasi dimensiune!\n";
        exit(EXIT_FAILURE);
    }

    else
    {
        Vector *v=new Vector(0,v1.nr);
        for(int i=0;i<v1.nr;i++)
            v->vect[i]=v1.vect[i]-v2.vect[i];
            return *v;
    }
}

inline bool operator==(Vector &v1, Vector& v2)
{
    if(v1.nr!=v2.nr)
        return false;

    else
    {
        for(int i=0;i<v1.nr;i++)
            if(v1.vect[i]!=v2.vect[i])
                 return false;
        return true;
    }
}

inline bool operator!=(Vector &v1, Vector& v2)
{
    if(v1.nr!=v2.nr)
        return true;

    else
    {
        for(int i=0;i<v1.nr;i++)
            if(v1.vect[i]!=v2.vect[i])
                 return true;
        return false;
    }
}

int length(Vector &v)
{
   return v.nr;
}

double elem(Vector &v, int i)
{
    return v.vect[i];
}

void menu_output()
{
    cout<<"\n Petre-Vlad Mihaela - Grupa 212 - Proiect 1 - Tema 14\n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"Optiuni:\n\n";
    cout<<"1. Introduceti nr. de vectori\n";
    cout<<"2. Setati vectorii\n";
    cout<<"3. Suma vectorilor\n";
    cout<<"4. Maximul vectorilor\n";
    cout<<"5. Stergeti consola\n";
    cout<<"0. Iesire\n";
}
void menu()
{
    int option=0;///optiunea aleasa din meniu
    int nrv=0,i,el_setate=0,pauza=0,afis=0;
    Vector *v;

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
            cout<<"\nNr. vectori = ";cin>>nrv;
            while(nrv<=0)
            {
                cout<<"\nDati un numar pozitiv nenul.\n";
                cout<<"\nNr. vectori = ";cin>>nrv;
            }
        }

        if(option==2)
        {
            if(nrv==0)
                cout<<"\nNu ati dat nr. de vectori!\n";

            else
            {
                v=new Vector(nrv);
                for(i=0;i<nrv;i++)
                {
                    cout<<"\nCititi vectorul "<<i+1<<"\n";
                    cin>>v[i];
                }
                el_setate=1;
            }
        }

        if (option==3)
        {
            if(nrv==0)
                cout<<"\nNu ati dat nr. de vectori!\n";

            else if(el_setate==0)
                cout<<"\nNu ati setat vectorii!\n";

            else
            {
            Vector suma=v[0];
            for(i=1;i<nrv;i++)
                suma=suma+v[i];

            cout<<"\nVectorul suma este : "<<suma<<"\n";
            pauza=1;
            }
        }

        if (option==4)
        {

            if(nrv==0)
                cout<<"\nNu ati dat nr. de vectori!\n";

            else if(el_setate==0)
                cout<<"\nNu ati setat vectorii!\n";

            else
            {
                int l[nrv],dim_dif=0;

                for(i=0;i<nrv;i++)
                    l[i]=length(v[i]);

                for(i=1;i<nrv;i++)
                    if(l[i]!=l[i-1])
                    {
                        dim_dif=1;
                        break;
                    }
                if(dim_dif==1)
                {
                    cout<<"\nVectorii au dimensiuni diferite.\n";
                    cout<<"Daca un singur vector are dim. maxima, il alegem ca maxim.\n";
                    cout<<"Altfel, comparam elementele vectorilor cu dim. cea mai mare.\n\n";

                    int l_max=l[0];
                    for(i=1;i<nrv;i++)
                        if(l[i]>l[i-1])
                            l_max=l[i];

                    int nr=0;
                    for(i=0;i<nrv;i++)
                        if(l[i]==l_max)
                            nr++;

                    if(nr==1)
                    {
                        cout<<"Un singur vector are dim. maxima "<<l_max<<".\n";

                        for(i=0;i<nrv;i++)
                            if(l[i]==l_max)
                            {
                                cout<<"Asadar, vectorul maxim este: "<<v[i]<<"\n";
                                break;
                            }
                     }
                     else
                     {
                         cout<<nr<<" vectori au dim. maxima "<<l_max<<":\n";

                         Vector v_max[nr];int j=0;

                         for(i=0;i<nrv;i++)
                             if(l[i]==l_max)
                             {
                                 v_max[j++]=v[i];
                                 cout<<v_max[j-1];
                             }

                        Vector maxim=v_max[0];

                        int egale=1;

                        for(i=1;i<nr;i++)
                        {
                            if(v_max[i]!=maxim)
                            {
                                egale=0;break;
                            }
                        }
                        if(egale==1)
                            cout<<"Vectorii sunt egali.\n\n";
                        else
                        {
                            int p=0,egale=1;
                            while(p!=l[0])
                            {
                                for(i=1;i<nr;i++)
                                    if(elem(v_max[i],p) != elem(maxim,p))
                                    {
                                        egale=0;break;
                                    }
                                if(egale==1)
                                {
                                    p++;continue;
                                }
                                else
                                {
                                    for(j=i;j<nr;j++)
                                        if(elem(v_max[j],p) > elem(maxim,p))
                                            maxim=v_max[j];
                                    cout<<"Vectorul maxim este: "<<maxim<<"\n";
                                    break;
                                }
                            }
                        }
                     }
                }
                else
                {
                    cout<<"\nVectorii au aceeasi dimensiune.\n";
                    cout<<"Comparam elementele vectorilor.\n\n";

                    Vector maxim=v[0];

                    int egale=1;
                    for(i=1;i<nrv;i++)
                    {
                        if(v[i]!=maxim)
                        {
                            egale=0; break;
                        }
                    }
                    if(egale==1)
                        cout<<"Vectorii sunt egali.\n\n";
                    else
                    {
                        int p=0,egale=1;
                        while(p!=l[0])
                        {
                            for(i=1;i<nrv;i++)
                                if(elem(v[i],p) != elem(maxim,p))
                                {
                                    egale=0; break;
                                }
                            if(egale==1)
                            {
                                p++; continue;
                            }
                            else
                            {
                                for(int j=i;j<nrv;j++)
                                    if(elem(v[j],p) > elem(maxim,p))
                                        maxim=v[j];
                                cout<<"Vectorul maxim este: "<<maxim<<"\n";
                                break;
                            }
                        }
                    }
                }
                pauza=1;
            }
        }

        if(option==5)
        {
            system("cls"); ///Sterge continutul curent al consolei
            afis=0;
        }

        if (option==0)
        {
            cout<<"\nEXIT!\n";
        }

        if (option<0||option>5)
        {
            cout<<"\nSelectie invalida\n";
        }

        if(pauza==1)
        {
            system("pause"); ///Pauza - Press any key to continue...
            pauza=0;
        }
    }
    while(option!=0);
}

int main()
{
    menu();
    return 0;
}
