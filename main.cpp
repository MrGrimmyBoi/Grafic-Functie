#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#define pi 3.14159265359
using namespace std;
int param[100];
struct point
{
    float x,y;
};
struct node_str
{
    string inf;
    node_str* succ;
};
struct node_float
{
    float inf;
    node_float* succ;
};
void push(node_str* &St, string data)
{
    if(St==NULL)
    {
        node_str* q=new node_str;
        q->inf=data;
        q->succ=NULL;
        St=q;
    }
    else
    {
        node_str* q=new node_str;
        q->inf=data;
        q->succ=St;
        St=q;
    }
}
void push(node_float* &Sf, float data)
{
    if(Sf==NULL)
    {
        node_float* p=new node_float;
        p->inf=data;
        p->succ=NULL;
        Sf=p;
    }
    else
    {
        node_float* p=new node_float;
        p->inf=data;
        p->succ=Sf;
        Sf=p;
    }
}
void pop(node_str* &St)
{
    if(St==NULL)
        cout<<"Erorare, stiva este vida";
    else
    {
        node_str* q=new node_str;
        q=St;
        St=St->succ;
        delete(q);
    }
}
void pop(node_float* &St)
{
    if(St==NULL)
        cout<<"Erorare, stiva este vida";
    else
    {
        node_float* p=new node_float;
        p=St;
        St=St->succ;
        delete(p);
    }
}
string top(node_str* St)
{
    return St->inf;
}
float top(node_float* St)
{
    return St->inf;
}

void inlocuieste_functii(string &dest)
{
    while(dest.find("sin")<dest.length())
        dest.replace(dest.begin()+dest.find("sin"),dest.begin()+dest.find("sin")+3,"!");

    while(dest.find("cos")<dest.length())
        dest.replace(dest.begin()+dest.find("cos"),dest.begin()+dest.find("cos")+3,"@");

    while(dest.find("arctg")<dest.length())
        dest.replace(dest.begin()+dest.find("arctg"),dest.begin()+dest.find("arctg")+5,"#");

    while(dest.find("arcctg")<dest.length())
        dest.replace(dest.begin()+dest.find("arcctg"),dest.begin()+dest.find("arcctg")+6,"?");

    while(dest.find("ln")<dest.length())
        dest.replace(dest.begin()+dest.find("ln"),dest.begin()+dest.find("ln")+2,"&");

    while(dest.find("lg")<dest.length())
        dest.replace(dest.begin()+dest.find("lg"),dest.begin()+dest.find("lg")+2,"_");

    while(dest.find("sqrt")<dest.length())
        dest.replace(dest.begin()+dest.find("sqrt"),dest.begin()+dest.find("sqrt")+4,"|");
}
int prioritate(char c)
{
    if(c=='^' || c=='!' || c=='@' || c=='#' || c=='?' || c=='&' || c=='_' || c=='|')
        return 3;
    else if(c=='*' || c=='/')
        return 2;
    else if(c=='+' || c=='-')
        return 1;
    else
        return -1;
}
void postfixat(string &input)
{
    node_str* St=new node_str;
    push(St, "end");
    int lung=input.length();
    string aux="",temp; //Vom folosi acest auxiliar pentru a rearanja functia fara sa stricam string-ul original
    for(int i=0; i<lung; i++)
     if((input[i]>='a' && input[i]<='z') || (int)input[i]<=0 ) //Verificam daca un caracter este o variabila sau un numar
              aux+=input[i];
            //Daca este atunci il concatenam in auxiliarul nostru
        else if(input[i]=='(') //Verificam daca am dat peste o paranteza
            push(St,temp+'('); //o punem in stack pentru a sti pana unde sa scoatem elementele atunci cand gasim o paranteza inchisa
        else if(input[i]==')')
        {
            while(top(St)!="end" && top(St)[0]!='(')
            {
                string c=top(St);           //Scoatem elementele din stack pana acesta este gol sau dam peste o paranteza deschisa si
                pop(St);                    //punem fiecare element in auxiliar
                aux+=c;
            }
            if(top(St)[0]=='(')       //Verificam daca am ramas cu o paranteza deschisa
                pop(St);            //daca aceasta se afla in varful stivei, atunci o scoatem
        }
        else if(input[i]=='[')
            push(St,temp+'[');
        else if(input[i]==']')
        {
            while(top(St)!="end" && top(St)[0]!='[')
            {
                string c=top(St);
                pop(St);
                aux+=c;
            }
            if(top(St)[0]=='[')
                pop(St);
        }
        else if(input[i]=='{')
            push(St,temp+'{');
        else if(input[i]=='}')
        {
            while(top(St)!="end" && top(St)[0]!='}')
            {
                string c=top(St);
                pop(St);
                aux+=c;
            }
            if(top(St)=="{")
                pop(St);
        }
        else
        {
            while(top(St)!="end" && prioritate(input[i])<=prioritate(top(St)[0])) //Cand ajungem aici inseamna ca am ajuns pe un operator
            {
                //si verificam daca prioritatea acestuia esta mai mare decat
                string c=top(St);                                                     //al operatorului din stiva
                pop(St);                                                              //cat timp conditia este adevarata, continuam sa punem
                aux+=c;                                                                   //elementele din stiva in auxiliar
            }
            string b;                                                                     //punem operatorul din functia originala in stiva
            b+=input[i];
            push(St,b);
        }
    while(top(St)!="end")
    {
        string c = top(St);                            //La final adaugam tot ce a ramas pe stiva in auxiliar
        pop(St);
        aux+=c;
    }
    input=aux;            //Scriem functia modificata peste cea originala
}

int lung_nr(int nr)
{
    if(nr)
        return 1+lung_nr(nr/10);
    else
        return 0;
}
void inlocuieste_numere(string &str)
{
    int nr;
    char cons=-128;
    string aux=str,first,temp;    //Punem din nou functia intr-un auxiliar pentru a ne ajuta la prelucrare
    while(aux.find("+")<aux.length())                                           //Aici vom scoate toti operatorii si ii vom inlocui cu spatii pentru
    {
        //a avea acces la fiecare operand
        aux.replace(aux.begin()+aux.find("+"),aux.begin()+aux.find("+")+1," ");
    }
    while(aux.find("-")<aux.length())
    {
        aux.replace(aux.begin()+aux.find("-"),aux.begin()+aux.find("-")+1," ");
    }
    while(aux.find("*")<aux.length())
    {
        aux.replace(aux.begin()+aux.find("*"),aux.begin()+aux.find("*")+1," ");
    }
    while(aux.find("/")<aux.length())
    {
        aux.replace(aux.begin()+aux.find("/"),aux.begin()+aux.find("/")+1," ");
    }
    while(aux.find("^")<aux.length())
    {
        aux.replace(aux.begin()+aux.find("^"),aux.begin()+aux.find("^")+1," ");
    }
    aux+=" ";           //Adaugam un spatiu la final ca se supara functia pe mine daca nu :)
    while(aux.length()>0)  //Cat timp mai avem un operand in auxiliar, il vom extrage si vom verifica daca este un numar
    {
        stringstream(aux)>>first;       //extragem pe rand cate un operand
        if(stringstream(first)>>nr)     //nr este de tip int, deci la finalul instructiunii aceasta va returna 0 daca operandul nu este un nr
        {
            //sau v-a returna adevarat daca operandul este un numar si-l va seta pe nr ca acel numar
            param[(int)cons+129]=nr;
            str.replace(str.begin()+str.find(first),str.begin()+str.find(first)+lung_nr(nr),temp+cons); //inlocuim in functia originala nr cu acel caracter
            cons++;                   //il incrementam pe cons
        }
        aux.erase(aux.begin(),aux.begin()+first.length()+1); //stergem operandul pe care l-am verificat

    }
}

float calc_fct(char input, float op1, float op2)
{
    //Un mare if-else care verifica ce operatie ar trebui sa fie executata si returneaza rezultatul acesteia
    if(input=='+')
        return op1+op2;
    else if(input=='-')
        return op1-op2;
    else if(input=='*')
        return op1*op2;
    else if(input=='/')
        return op1/op2;
    else if(input=='^')
        return pow(op1,op2);
    else if(input=='!')
        return sin(op1*(pi/180));
    else if(input=='@')
        return cos(op1*(pi/180));
    else if(input=='#')
        return atan(op1*(pi/180));
    else if(input=='?')
        return atan(1/(op1*(pi/180)));
    else if(input=='&')
        return log(op1);
    else if(input=='_')
        return log10(op1);
    else
        return sqrt(op1);
}

float evalueazafunctia(string s, float valoare_in_punct)
{
    node_float* arr=new node_float;                 //Declaram o stiva pe care o vom folosi ca sa calculam functia
    arr=NULL;
    string binary="+-*^/|";                         //Un string in care punem operatiile care necesita doi operanzi pentru a ne usura cautarea
    float op1,op2,rezultat;
    for(int i=0; i<s.size(); i++)                   //Parcurgem functia si luam fiecare caracter in parte
        if(s[i]<0)                                  //Verificam daca suntem pe un numar
            push(arr,param[(int)s[i]+129]);              //Punem numarul in stiva
        else if(s[i]=='x')                              //Verificam daca suntem pe variabila
            push(arr,valoare_in_punct);           //Punem valoarea variabilei in stiva
        else
        {
            if(binary.find(s[i])<binary.length())         //Verificam daca suntem pe un operator binar
            {

                op2=top(arr);
                pop(arr);     //Scoatem ultimele doua elemente de pe stiva
                op1=top(arr);
                pop(arr);
                rezultat=calc_fct(s[i],op1,op2);        //Calculam valoarea operatiei
                push(arr,rezultat);               //Punem valoarea inapoi in stiva
            }
            else
            {
                //Cand ajungem in cazul acesta inseamna ca suntem pe un operator unar
                op1=top(arr);
                pop(arr);     //Scoatem ultimul element din stiva
                rezultat=calc_fct(s[i],op1,0);          //Calculam valoarea operatiei
                push(arr,rezultat);               //Punem valoarea inapoi in stiva
            }
        }
    return top(arr);                          //Returnam rezultatul
}


void set_curve(sf::VertexArray &curve, string functie, point Origine, float start, float finish, float step, int r, int g, int b)
{
    //Luam un set de variabile pentru a face distinctia intre 4 tipuri de functii pentru programul nostru
    bool trig=0,bin=0;
    unsigned nr_trig=0,nr_bin=0;
    string fct="!@#?_|&",aux;
    //Numaram cate functii trigonometrice avem
    for(int i=0; i<7; i++)
    {
        aux=functie;
        while(aux.find(fct[i])<aux.length())
        {
            nr_trig++;
            trig=1;
            aux.replace(aux.begin()+aux.find(fct[i]),aux.begin()+aux.find(fct[i])+1," ");
        }

    }
    //Numaram cate operatii de adunare scadere, inmultire si impartire avem
    aux=functie;
    fct="+-*/";
    for(int i=0; i<4; i++)
        while(aux.find(fct[i])<aux.length())
        {
            nr_bin++;
            if(trig && (fct[i]!='*' || fct[i]!='/'))
                bin=1;
            if(trig && (fct[i]=='*' || fct[i]=='/'))
                nr_bin--;
            aux.replace(aux.begin()+aux.find(fct[i]),aux.begin()+aux.find(fct[i])+1," ");
        }
    cout<<nr_trig<<"            "<<nr_bin<<"            "<<(nr_trig==1+nr_bin)<<endl;
    //Compunem graficul atasand cate un punct pe rand
    for (float x = start; x < finish; x += step)
    {
        //Adaugam punctele relativ de origine si le impartim in 4 tipuri de functii: 1-Obtinute prin adunarea,scaderea,inmultirea,impartirea functiilor trigonometrice/logaritmice
        //                                                                           2-Obtinute prin adaugarea, scaderea, inmultirea, impartirea la o functie trigonometrica a unei functii de tip a*x
        //                                                                           3-Polinomiale
        //                                                                           4-Functii trigonometrice
        curve.append(sf::Vertex(sf::Vector2f(Origine.x+x*(nr_trig==1+nr_bin ? (.40/10) : ((trig && bin) || (!trig && !bin)) ? 1 : (.40/10) ),
                                             Origine.y-evalueazafunctia(functie,x*(nr_trig==1+nr_bin ? (10/3.9) : ((trig && bin) || (!trig && !bin))? 1 : (10/3.9)))),sf::Color(r,g,b)));
    }
}

int main()
{
    //Pregatim variabilele pe care le vom folosi in program
    unsigned nr_fct, nr_lang_packs=2,index_lang;
    float zoom_cam=13.f;
    bool is_zoomed=0;
    point Origine,camera;
    camera.x=Origine.x=500.f;
    camera.y=Origine.y=500.f;
    //Declaram limbile in care va fi disponibil meniul si dam voie utilizatorului sa o aleaga pe cea pe care o preferea
    string fct[10],language[5][5]= {{"1-Romana","Dati numarul de functii: ", "Dati functia nr.","Graficul functiei"},
        {"2-English","Type the number of functions you want to plot: ","Type the function #","The graphic of the function"}
    };
    for(int i=0; i<nr_lang_packs; i++)
        cout<<language[i][0]<<endl;
    cin>>index_lang;
    index_lang--;
    //Citim numarul de functii ce vor fi introduse
    cout<<language[index_lang][1];
    cin>>nr_fct;
    //Citim functiile si le procesam in acelasi timp
    for(int i=0; i<nr_fct; i++)
    {
        cout<<language[index_lang][2]<<i+1<<": ";
        cin>>fct[i];
        inlocuieste_numere(fct[i]);
        inlocuieste_functii(fct[i]);
        postfixat(fct[i]);
    }
    cout<<fct[0]<<endl;
    //Declaram ecranul pe care vom desena functiile si ne pregatim un set de lucruri necesare precum un ceas pe care-l vom folosi ca sa punem un mic delay intre apasari,
    //camera si doua linii, care sunt axele de coordonate
    sf::RenderWindow window(sf::VideoMode(1080, 720), language[index_lang][3]);
    sf::View view;
    sf::Clock clock;
    view.setCenter(sf::Vector2f(camera.x, camera.y));
    view.setSize(sf::Vector2f(zoom_cam, zoom_cam));
    sf::Vertex x_line[] =
    {
        sf::Vertex(sf::Vector2f(0.f, 500.f)),
        sf::Vertex(sf::Vector2f(1000.f, 500.f))
    };
    sf::Vertex y_line[] =
    {
        sf::Vertex(sf::Vector2f(500.f, 0.f)),
        sf::Vertex(sf::Vector2f(500.f, 1000.f))
    };
    //Declaram un vector de VertexArray in care vom stoca diferite grafice pe care le doreste utilizatorul,
    //iar pentru inceput introducem constructori ale acestor VertexArray-uri
    vector<sf::VertexArray> ArrayOfCurves;
    for(int i=0; i<nr_fct; i++)
        ArrayOfCurves.push_back(sf::VertexArray(sf::PrimitiveType::LineStrip));
    //Declaram un vector de thread-uri care este foarte important pentru a obtine ceva mai multa performanta
    //Pe fiecare thread vom pune functia de desenat pentru a putea sa trecem mai departe in timp ce desenam unul din grafice
    vector<std::thread> threads;
    for(int i=0; i<nr_fct; i++)
    {
        threads.push_back(std::thread(set_curve, std::ref(ArrayOfCurves[i]),fct[i],Origine,-10000.0,10000.0,0.1, 1+rand()%255, 1+rand()%255, 1+rand()%255));
        threads[i].join();
    }

    //Doua ultime setari pentru a face totul sa arate bine
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //Declaram un timer pentru a vedea cat timp a trecut de la ultima apasare
        sf::Time timer=clock.getElapsedTime();
        //O conditie pentru a implementa functia de zoom out
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) && timer.asSeconds()>=0.25)
        {
            zoom_cam+=5.f;
            view.setSize(sf::Vector2f(abs(zoom_cam), abs(zoom_cam)));
            clock.restart();
        }
        //O alta conditie pentru functia de zoom in
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add) && timer.asSeconds()>=0.25 && zoom_cam>5)
        {
            zoom_cam-=5.f;
            view.setSize(sf::Vector2f(abs(zoom_cam), abs(zoom_cam)));
            clock.restart();
        }
        //Niste conditii pentru a putea muta camera
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && timer.asSeconds()>=0.25)
        {
            camera.x-=2.f;
            view.setCenter(sf::Vector2f(camera.x,camera.y));
            clock.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && timer.asSeconds()>=0.25)
        {
            camera.x+=2.f;
            view.setCenter(sf::Vector2f(camera.x,camera.y));
            clock.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && timer.asSeconds()>=0.25)
        {
            camera.y-=2.f;
            view.setCenter(sf::Vector2f(camera.x,camera.y));
            clock.restart();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && timer.asSeconds()>=0.25)
        {
            camera.y+=2.f;
            view.setCenter(sf::Vector2f(camera.x,camera.y));
            clock.restart();
        }
        //Folosim click dreapta ca un buton de reset
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)  && timer.asSeconds()>=0.25)
        {
            view.setCenter(sf::Vector2f(Origine.x,Origine.y));
            view.setSize(sf::Vector2f(13.f, 13.f));
            camera.x=Origine.x;
            camera.y=Origine.y;
            is_zoomed=0;
            clock.restart();
            zoom_cam=13.0f;
        }
        //Stergem ecranul precedent, setam privirea pentru acolo unde se afla camera, desenam graficele si apoi axele de coordonate, dupa care afisam totul
        window.clear();
        window.setView(view);
        for(int i=0; i<nr_fct; i++)
            window.draw(ArrayOfCurves[i]);
        window.draw(x_line, 2, sf::Lines);
        window.draw(y_line, 2, sf::Lines);
        window.display();
    }
    return 0;
}
//zip:E1_nume-proiect_Nume1_Nume2
//In zip: Proiectul (folder) + Filmulet de prezentare
//Adresa:bpatrut@gmail.com
