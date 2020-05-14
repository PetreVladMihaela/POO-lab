#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <typeinfo>

using namespace std;

class examen
{
protected:
    static int n;
    int id;
    string materie;
    double nota_scris;

public:
    examen(string, double);
    virtual ~examen();
    examen& operator=(examen &e);

    virtual void citire (istream &in);
    virtual void afisare(ostream &out);
    friend istream& operator>>(istream&, examen&);
    friend ostream& operator<<(ostream&, examen&);

    static void nr_examene() { cout<<n<<"\n"; }
};

int examen::n;

examen::examen(string m="", double nota=0)
{
    n++; id=n;
    materie=m;
    try
    {
        if (nota<0 || nota>10)
            throw nota;
    }
    catch (double x)
    {
        cout<<"\nEroare in constructorul clasei examen, nota la scris nu poate fi negativa sau mai mare decat 10.\n";
        exit(EXIT_FAILURE);
    }
    nota_scris=nota;
}

examen::~examen() { }

examen& examen::operator=(examen &e)
{
    if (this!=&e)
    {
        id=e.id;
        materie=e.materie;
        nota_scris=e.nota_scris;
    }
    return *this;
}

void examen::citire(istream &in)
{
    string m;
    cout<<"Materie: "; in>>m; materie=m;

    double nota;
    cout<<"Nota la scris: "; in>>nota;
    try
    {
        if (nota<0 || nota>10)
            throw nota;
    }
    catch (double x)
    {
        cout<<"\nEroare la citire, nota la scris nu poate fi negativa sau mai mare decat 10.\n";
        exit(EXIT_FAILURE);
    }
    nota_scris=nota;
}

void examen::afisare(ostream &out)
{
    out<<"Id_examen: "<<id<<"\n";
    out<<"Materie: "<<materie<<"\n";
    out<<"Nota la scris: "<<nota_scris<<"\n";
}

istream& operator>>(istream& in, examen& e)
{
    e.citire(in);
    return in;
}

ostream& operator<<(ostream& out, examen& e)
{
    e.afisare(out);
    return out;
}

class partial:public examen
{
protected:
    double nota_oral;

public:
    partial(string, double, double);
    ~partial();
    partial& operator=(partial &p);

    virtual void citire (istream &in);
    virtual void afisare(ostream &out);
    friend istream& operator>>(istream&, partial&);
    friend ostream& operator<<(ostream&, partial&);

    double get_nota_scris() const { return nota_scris; }
    double get_nota_oral() const { return nota_oral; }

    friend void refacere(partial &f)
    {
        if(f.nota_scris >= 5 && f.nota_oral >= 5)
        {
            cout<<"Partialul la "<<f.materie<<" este luat.\n";
        }
        else
        {
            cout<<"Refacere partial de "<<f.materie<<":\n";

            double nota;
            if(f.nota_scris < 5)
            {
                cout<<"Nota noua la scris: "; cin>>nota;
                try
                {
                    if (nota<0 || nota>10)
                        throw nota;
                }
                catch (double x)
                {
                    cout<<"\nEroare la citire, nota la scris nu poate fi negativa sau mai mare decat 10.\n";
                    exit(EXIT_FAILURE);
                }
                f.nota_scris=nota;
            }

            if(f.nota_oral < 5)
            {
                cout<<"Nota noua la oral: "; cin>>nota;
                try
                {
                    if (nota<0 || nota>10)
                        throw nota;
                }
                catch (double x)
                {
                    cout<<"\nEroare la citire, nota la oral nu poate fi negativa sau mai mare decat 10.\n";
                    exit(EXIT_FAILURE);
                }
                f.nota_oral=nota;
            }
        }
    }
};

partial::partial(string m="", double ns=0, double no=0):examen(m,ns)
{
    try
    {
        if (no<0 || no>10)
            throw no;
    }
    catch (double x)
    {
        cout<<"\nEroare in constructorul clasei partial, nota la oral nu poate fi negativa sau mai mare decat 10.\n";
        exit(EXIT_FAILURE);
    }
    nota_oral=no;
}

partial::~partial() { }

partial& partial::operator=(partial &p)
{
    if (this!=&p)
    {
        examen::operator=(p);
        nota_oral=p.nota_oral;
    }
    return *this;
}

void partial::citire(istream &in)
{
    examen::citire(in);

    double nota;
    cout<<"Nota la oral: "; in>>nota;
    try
    {
        if (nota<0 || nota>10)
            throw nota;
    }
    catch (double x)
    {
        cout<<"\nEroare la citire, nota la oral nu poate fi negativa sau mai mare decat 10.\n";
        exit(EXIT_FAILURE);
    }
    nota_oral=nota;
}

void partial::afisare(ostream &out)
{
    examen::afisare(out);
    out<<"Nota la oral: "<<nota_oral<<"\n";
}

istream& operator>>(istream& in, partial& p)
{
    p.citire(in);
    return in;
}

ostream& operator<<(ostream& out, partial& p)
{
    p.afisare(out);
    return out;
}

class e_final:public partial
{
    double nota_proiect;

public:
    e_final(string, double, double, double);
    ~e_final();
    e_final& operator=(e_final &f);

    void citire (istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream&, e_final&);
    friend ostream& operator<<(ostream&, e_final&);
};

e_final::e_final(string m="", double ns=0, double no=0, double extra=0):partial(m,ns,no)
{
    try
    {
        if (extra<0 || extra>10)
            throw extra;
    }
    catch (double x)
    {
        cout<<"\nEroare in constructorul clasei e_final, nota la proiect nu poate fi negativa sau mai mare decat 10.\n";
        exit(EXIT_FAILURE);
    }
    nota_proiect=extra;
}

e_final::~e_final() { }

e_final& e_final::operator=(e_final &f)
{
    if (this!=&f)
    {
        partial::operator=(f);
        nota_proiect=f.nota_proiect;
    }
    return *this;
}

void e_final::citire(istream &in)
{
    partial::citire(in);

    double nota;
    cout<<"Nota la proiect: "; in>>nota;
    try
    {
        if (nota<0 || nota>10)
            throw nota;
    }
    catch (double x)
    {
        cout<<"\nEroare la citire, nota la proiect nu poate fi negativa sau mai mare decat 10.\n";
        exit(EXIT_FAILURE);
    }
    nota_proiect=nota;
}

void e_final::afisare(ostream &out)
{
    partial::afisare(out);
    out<<"Nota la proiect: "<<nota_proiect<<"\n";
}

istream& operator>>(istream& in, e_final& f)
{
    f.citire(in);
    return in;
}

ostream& operator<<(ostream& out, e_final& f)
{
    f.afisare(out);
    return out;
}

class quiz:public e_final
{
    int itemi_corecti;
    double pct_per_item;
    double punctaj;

public:
    quiz(string, double, double, double, int, double);
    ~quiz();
    quiz& operator=(quiz &q);
    void citire (istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream&, quiz&);
    friend ostream& operator<<(ostream&, quiz&);
};

quiz::quiz(string m="", double ns=0, double no=0, double extra=0, int ic=0, double val=0):e_final(m,ns,no,extra)
{
    try
    {
        if (ic<0 || val<0)
            throw -1;
    }
    catch (int neg)
    {
        cout<<"\nEroare in constructorul clasei quiz.\n";
        exit(EXIT_FAILURE);
    }
    itemi_corecti=ic;
    pct_per_item=val;
    punctaj=ic*val;
}

quiz::~quiz(){};

quiz& quiz::operator=(quiz &q)
{
    if (this!=&q)
    {
        e_final::operator=(q);
        itemi_corecti=q.itemi_corecti;
        pct_per_item=q.pct_per_item;
        punctaj=q.punctaj;
    }
    return *this;
}

void quiz::citire(istream &in)
{
    e_final::citire(in);

    int nr_c;
    cout<<"Introduceti nr. de itemi ai grilei la care studentul a raspuns corect: ";
    in>>nr_c;
    try
    {
        if (nr_c<0)
            throw nr_c;
    }
    catch (int x)
    {
        cout<<"\nEroare la citire, nr. de itemi nu poate fi negativ.\n";
        exit(EXIT_FAILURE);
    }
    double p;
    cout<<"Dati punctajul per item: ";
    in>>p;
    try
    {
        if (p<0)
            throw p;
    }
    catch (double x)
    {
        cout<<"\nEroare la citire, punctajul per item nu poate fi negativ.\n";
        exit(EXIT_FAILURE);
    }
    itemi_corecti=nr_c;
    pct_per_item=p;
    punctaj=nr_c*p;
}

void quiz::afisare(ostream &out)
{
    e_final::afisare(out);
    out<<"Punctaj quiz: "<<punctaj<<"\n";
}

istream& operator>>(istream& in, quiz& q)
{
    q.citire(in);
    return in;
}

ostream& operator<<(ostream& out, quiz& q)
{
    q.afisare(out);
    return out;
}

template <class t> class CatalogIndividual
{
    static int nr;
    int nr_matricol;
    int nr_examene;
    vector<t> e;

public:
    CatalogIndividual(vector<t> v=vector<t>())
    {
        nr++;
        nr_matricol=nr;
        nr_examene=v.size();

        for (auto i = v.begin(); i != v.end(); i++)
            e.push_back(*i);
    }

    ~CatalogIndividual(){}

    CatalogIndividual& operator=(CatalogIndividual &c)
    {
        if (this!=&c)
        {
            nr_matricol=c.nr_matricol;
            nr_examene=c.nr_examene;
            for(auto i=c.e.begin(); i != c.e.end(); i++)
                e.push_back(*i);
        }
        return *this;
    }

    friend istream& operator >>(istream &in, CatalogIndividual <t> &c)
    {
        int nr_ex;
        cout<<"Introduceti nr. de examene: ";
        in>>nr_ex; cout<<"\n";
        try
        {
            if(nr_ex<0)
                throw nr_ex;
        }
        catch (int x)
        {
            cout<<"\nEroare, numarul nu poate fi mai mic decat 0.\n";
            exit(EXIT_FAILURE);
        }
        c.nr_examene=nr_ex;
        if(nr_ex>0)
        {
            t ex[nr_ex];
            for(int i=0;i<c.nr_examene;i++)
            {
                cout<<"Introduceti examenul "<<i+1<<":\n";
                in>>ex[i];
                c.e.push_back(ex[i]);
                cout<<"\n";
            }
        }
        return in;
    }

    friend ostream& operator <<(ostream &out, CatalogIndividual <t> &c)
    {
        if(c.nr_examene==0)
            out<<"In catalog nu sunt inca examene.\n\n";

        else
        {
            out<<"Nr. matricol: "<<c.nr_matricol<<"\n\n";
            for(int i=0;i<c.nr_examene;i++)
                out<<c.e[i]<<"\n";
        }
        return out;
    }

    friend void operator+=(CatalogIndividual<t>& c, t& ex)
    {
        c.nr_examene++;
        c.e.push_back(ex);
    }

    int get_nr_ex() const { return nr_examene; }
};

template <class t> int CatalogIndividual<t>::nr;

template <> class CatalogIndividual<quiz>
{
    static int nr1;
    int nr_matricol;
    int nr_quizuri;
    vector<quiz> q;
public:

    CatalogIndividual(vector<quiz> v=vector<quiz>())
    {
        nr1++;
        nr_matricol=nr1;
        nr_quizuri=v.size();

        for (auto i = v.begin(); i != v.end(); i++)
            q.push_back(*i);
    }

    ~CatalogIndividual(){}

    CatalogIndividual& operator=(CatalogIndividual &c)
    {
        if (this!=&c)
        {
            nr_matricol=c.nr_matricol;
            nr_quizuri=c.nr_quizuri;
            for(auto i=c.q.begin(); i != c.q.end(); i++)
                q.push_back(*i);
        }
        return *this;
    }

    friend istream& operator >>(istream &in, CatalogIndividual <quiz> &c)
    {
        int nr_q;
        cout<<"Introduceti nr. de quizuri date de student: ";
        in>>nr_q; cout<<"\n";
        try
        {
            if(nr_q<0)
                throw nr_q;
        }
        catch (int x)
        {
            cout<<"\nEroare, numarul nu poate fi mai mic decat 0.\n";
            exit(EXIT_FAILURE);
        }
        c.nr_quizuri=nr_q;
        if(nr_q>0)
        {
            quiz a[nr_q];
            for(int i=0;i<c.nr_quizuri;i++)
            {
                cout<<"Introduceti examenul "<<i+1<<" la care studentul a dat quiz:\n";
                in>>a[i];
                c.q.push_back(a[i]);
                cout<<"\n";
            }
        }
        return in;
    }

    friend ostream& operator <<(ostream &out, CatalogIndividual <quiz> &c)
    {
        if(c.nr_quizuri==0)
            out<<"Studentul cu nr. matricol "<<c.nr_matricol<<" nu a dat niciun quiz.\n\n";
        else if(c.nr_quizuri==1)
        {
            out<<"Studentul cu nr. matricol "<<c.nr_matricol<<" a dat quiz la un examen:"<<"\n";
            out<<c.q[0]<<"\n";
        }
        else
        {
            out<<"Studentul cu nr. matricol "<<c.nr_matricol<<" a dat quiz la "<<c.nr_quizuri<<" examene:"<<"\n\n";
            for(int i=0;i<c.nr_quizuri;i++)
                out<<c.q[i]<<"\n";
        }
        return out;
    }

    friend void operator+=(CatalogIndividual<quiz>& c, quiz& nq)
    {
        c.nr_quizuri++;
        c.q.push_back(nq);
    }

    friend void nr_min_2q(vector<CatalogIndividual<quiz>> q)
    {
        int min_2q=0;
        for(unsigned int i=0;i<q.size();i++)
            if(q[i].nr_quizuri>=2)
                min_2q++;
        if(min_2q==1)
            cout<<"\nO persoana a dat cel putin 2 quizz-uri.\n";
        else
            cout<<"\n"<<min_2q<<" persoane au dat cel putin 2 quizz-uri.\n";
    }

    int get_nr_q() const { return nr_quizuri; }
};
int CatalogIndividual<quiz>::nr1;

void menu_output()
{
    cout<<"\n Petre-Vlad Mihaela - Grupa 212 - Proiect 3 - Tema 3\n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"Optiuni:\n\n";
    cout<<"1. Dati nr. de studenti (default 1)\n";
    cout<<"2. Cititi numele si examenele studentilor\n";
    cout<<"3. Refacerea partialelor examenelor citite la 2\n";
    cout<<"4. Catalog individual - template (partial)\n";
    cout<<"5. Catalog individual - template (examen final)\n";
    cout<<"6. Catalog individual - template (quiz-specializare)\n";
    cout<<"7. Adaugarea unui examen intr-un catalog individual\n";
    cout<<"8. RTTI - typeid\n";
    cout<<"9. Contorizare examene\n";
    cout<<"10. Stergeti consola\n";
    cout<<"0. Iesire\n";
}

void tip(partial *&e, int i)
{
    string s;
    cout<<"\n";
    cout<<"Introduceti tipul examenului "<<i+1<<" (partial, final sau quiz): ";
    cin>>s;

    try
    {
        if(s=="partial")
        {
            e=new partial;
            cin>>*e;
        }
        else
            if(s=="final")
            {
                e=new e_final;
                cin>>*e;
            }
            else
                if(s=="quiz")
                {
                    e=new quiz;
                    cin>>*e;
                }
                else
                    throw -1;
    }
    catch (bad_alloc var)
    {
        cout << "Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
    catch(int t)
    {
        cout<<"Nu ati introdus un tip valid. Incercati partial, final sau quiz.\n ";
        exit(EXIT_FAILURE);
    }
}

void menu()
{
    int option=0, afis=0, nr_ex=0, i, j, nr_studenti=1;
    partial **ex;

    vector<partial> e_picate;
    unordered_map<string, vector<partial>> picati;

    vector<CatalogIndividual<partial>> p(1);
    vector<CatalogIndividual<e_final>> f(1);
    vector<CatalogIndividual<quiz>> q(1);

    const int nr_max_studenti = 1000;

    int nr_p, nr_f, nr_q; nr_p = nr_f = nr_q = 0;

    do
    {
        if(afis==0)
        {
            menu_output();
            afis=1;
        }

        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;

        if (option==1)
        {
            cout<<"\nNr. studenti (maxim 1000) = "; cin>>nr_studenti;

            while(nr_studenti<=0 || nr_studenti>nr_max_studenti)
            {
                cout<<"\nDati un numar pozitiv nenul mai mic sau egal cu 1000 .\n";
                cout<<"\nNr. studenti = "; cin>>nr_studenti;
            }
        }

        if(option==2)
        {
            for(i=0; i<nr_studenti; i++)
            {
                string nume;
                cout<<"\nNume student "<<i+1<<" : "; cin>>nume;

                cout<<"\nCititi examenele studentului :\n";

                cout<<"\nNr. examene = "; cin>>nr_ex;
                while(nr_ex<=0)
                {
                    cout<<"\nDati un numar pozitiv nenul.\n";
                    cout<<"\nNr. examene = "; cin>>nr_ex;
                }

                ex=new partial*[nr_ex];
                for(j=0; j<nr_ex; j++)
                {
                    tip(ex[j],j);

                    if(ex[j]->get_nota_scris()<5 || ex[j]->get_nota_oral()<5)
                        e_picate.push_back(*ex[j]);

                    partial *p1=dynamic_cast<partial*>(ex[j]);
                    e_final *p2=dynamic_cast<e_final*>(ex[j]);
                    quiz *p3=dynamic_cast<quiz*>(ex[j]);
                    if (p1) nr_p++;
                    if (p2) {nr_f++; nr_p--;}
                    if (p3) {nr_q++; nr_f--;}
                }

                if(e_picate.size()!=0)
                {
                    picati.insert(make_pair(nume,e_picate));
                    e_picate.clear();
                }

                cout<<"----------------------------------------------------\n";
                cout<<"\nAti citit urmatoarele examene pt. studentul "<<nume<<":\n";

                for(j=0; j<nr_ex; j++)
                        cout<<*ex[j]<<"\n";

                cout<<"----------------------------------------------------\n";
            }
        }

        if(option==3)
        {
            if(nr_ex==0)
                cout<<"\nNu ati citit niciun examen!\n";
            else
            {
                if(picati.size()==0)
                    cout<<"\nToate partialele examenelor date sunt luate.\n";
                else
                {
                    cout<<"Refacerea partialelor:\n";
                    for(auto x : picati)
                    {
                        cout<<"\nStudent: "<<x.first<<"\n";
                        for(unsigned int u=0; u<x.second.size(); u++)
                        {
                            cout<<x.second[u]<<"\n";
                            refacere(x.second[u]);
                            cout<<"\nNoua situatie:\n";
                            cout<<x.second[u]<<"\n";
                        }
                    }
                }
            }
        }

        if (option==4)
        {
            if(nr_studenti>1)
                p.resize(nr_studenti);

            for(i=0; i<nr_studenti; i++)
            {
                cout<<"\nStudentul "<<i+1<<":\n";
                cin>>p[i];
                cout<<"-------------------------\n";
                cout<<"\nCatalogul studentului "<<i+1<<":\n";
                cout<<p[i];
                cout<<"--------------------------\n";
                nr_p+=p[i].get_nr_ex();
            }
        }

        if (option==5)
        {
            if(nr_studenti>1)
                f.resize(nr_studenti);

            for(i=0; i<nr_studenti; i++)
            {
                cout<<"\nStudentul "<<i+1<<":\n";
                cin>>f[i];
                cout<<"-------------------------\n";
                cout<<"\nCatalogul studentului "<<i+1<<":\n";
                cout<<f[i];
                cout<<"-------------------------\n";
                nr_f+=f[i].get_nr_ex();
            }
        }

        if (option==6)
        {
            if(nr_studenti>1)
                q.resize(nr_studenti);

            for(i=0; i<nr_studenti; i++)
            {
                cout<<"\nStudentul "<<i+1<<":\n";
                cin>>q[i];
                cout<<"---------------------------------------\n\n";
                cout<<q[i];
                cout<<"---------------------------------------\n";
                nr_q+=q[i].get_nr_q();
            }
            nr_min_2q(q);
        }

        if(option==7)
        {
            string c;
            cout<<"In ce tip de catalog doriti sa adaugati un examen (partial, final sau quiz)?:";
            cin>>c;

            if(c!="partial" && c!="final" && c!="quiz")
            {
                cout<<"\nNu ati introdus un tip valid. Incercati partial, final sau quiz.\n ";
            }
            else
            {
                if(c=="partial")
                {
                    nr_p++;
                    if(nr_studenti>1)
                    {
                        cout<<"\nAlegeti catalogul in care se adauga un examen nou:\n";
                        do
                        {
                            cout<<"Dati un nr. intre 1 si "<<nr_studenti<<":";cin>>i;
                        }
                        while(i<1 || i>nr_studenti);

                        if(p.size()==1)
                        {
                            p.resize(nr_studenti);
                            cout<<"\nCatalogul ales:\n";
                            cout<<p[i-1];
                        }
                        else
                        {
                            cout<<"\n-------------------\n";
                            cout<<"\nCatalogul ales:\n";
                            cout<<p[i-1];
                            cout<<"---------------------\n";
                        }
                    }
                    else
                    {
                        i=1;
                        cout<<"\n----------------------------------------\n";
                        cout<<"\nCatalogul in care se va adauga examenul:\n";
                        cout<<p[0];
                        cout<<"------------------------------------------\n";
                    }

                    partial ep;
                    cout<<"\nIntroduceti un partial nou:\n";
                    cin>>ep;
                    p[i-1]+=ep;
                    cout<<"\n---------------------\n";
                    cout<<"\nCatalogul actualizat:\n";
                    cout<<p[i-1];
                    cout<<"---------------------\n";
                }
                else if(c=="final")
                {
                    nr_f++;
                    if(nr_studenti>1)
                    {
                        cout<<"\nAlegeti catalogul in care se adauga un examen nou:\n";
                        do
                        {
                            cout<<"Dati un nr. intre 1 si "<<nr_studenti<<":";cin>>i;
                        }
                        while(i<1 || i>nr_studenti);

                        if(f.size()==1)
                        {
                            f.resize(nr_studenti);
                            cout<<"\nCatalogul ales:\n";
                            cout<<f[i-1];
                        }
                        else
                        {
                            cout<<"\n-------------------\n";
                            cout<<"\nCatalogul ales:\n";
                            cout<<f[i-1];
                            cout<<"---------------------\n";
                        }
                    }
                    else
                    {
                        i=1;
                        cout<<"\n----------------------------------------\n";
                        cout<<"\nCatalogul in care se va adauga examenul:\n";
                        cout<<f[0];
                        cout<<"------------------------------------------\n";
                    }

                    e_final ef;
                    cout<<"\nIntroduceti un examen final nou:\n";
                    cin>>ef;
                    f[i-1]+=ef;
                    cout<<"\n---------------------\n";
                    cout<<"\nCatalogul actualizat:\n";
                    cout<<f[i-1];
                    cout<<"---------------------\n";
                }
                else
                {
                    nr_q++;
                    if(nr_studenti>1)
                    {
                        cout<<"\nAlegeti catalogul in care se adauga un examen nou:\n";
                        do
                        {
                            cout<<"Dati un nr. intre 1 si "<<nr_studenti<<":";cin>>i;
                        }
                        while(i<1 || i>nr_studenti);

                        if(q.size()==1)
                        {
                            q.resize(nr_studenti);
                            cout<<"\n"<<q[i-1];
                        }
                        else
                        {
                            cout<<"\n-----------------------------------------\n\n";
                            cout<<q[i-1];
                            cout<<"-----------------------------------------\n";
                        }
                    }
                    else
                    {
                        i=1;
                        cout<<"\n-----------------------------------------\n\n";
                        cout<<q[0];
                        cout<<"-----------------------------------------\n";
                    }

                    quiz eq;
                    cout<<"\nIntroduceti un quiz nou:\n";
                    cin>>eq;
                    q[i-1]+=eq;
                    cout<<"\n---------------------\n";
                    cout<<"\nCatalogul actualizat:\n";
                    cout<<q[i-1];
                    cout<<"---------------------\n";
                }
            }
        }

        if(option==8)
        {
            string c;
            cout<<"Dati tipul catalogului (partial, final sau quiz):";
            cin>>c;

            if(c!="partial" && c!="final" && c!="quiz")
            {
                cout<<"\nNu ati introdus un tip valid. Incercati partial, final sau quiz.\n ";
            }
            else
            {
                if(c=="partial")
                    cout << typeid(p[0]).name()<<"\n\n";

                else if(c=="final")
                    cout << typeid(f[0]).name()<<"\n\n";

                else
                    cout << typeid(q[0]).name()<<"\n\n";
            }
        }

        if(option==9)
        {
            cout<<"Nr. de examene create in timpul rularii acestui program pana acum este ";
            examen::nr_examene();
            cout<<"Nr. de partiale: "<<nr_p<<"\n";
            cout<<"Nr. de examene finale: "<<nr_f<<"\n";
            cout<<"Nr. de quizz-uri: "<<nr_q<<"\n\n";
        }

        if(option==10)
        {
            system("cls");
            afis=0;
        }

        if (option==0)
        {
            cout<<"\nEXIT!\n";
        }

        if (option<0||option>10)
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
