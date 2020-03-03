
/***************************************************************************
 *   Copyright (C) 2019 by Paco Andrés and Pilar Bachiller                 *
 *   pacoan@unex.es pilarb@unex.es                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "imageprocess.h"



void imageprocess::copiar(uchar * imgO, uchar * imgD, int tam)
{

    asm volatile(
            "movq %0, %%rsi;"
            "movq %1, %%rdi;"
            "movsxd %2, %%rcx;"
            "rep movsb;"
            :
            : "m" (imgO),	"m" (imgD), "m"(tam)
            : "%rcx", "%rsi", "%rdi", "memory"

    );

}

void imageprocess::borrar(uchar * imgD, int w, int h)
{
       /* dirDest = imgD;
        * tam = w*h
        * Para(p=0; p<tam; p++)
        * {
        * {[dirDest] = 0;
        * dirDest++;}
        * }
        */
    asm volatile(


    "movq %0 , %%rdi;" //Carga la imagenDestino
    "movsxd %1 , %%rbx;" //Carga w
    "movsxd %2 , %%rax;" //Carga h

    "imul %%rbx,%%rax;" //tam = w*h
    "mov $0 , %%rcx;" //pone p a 0


        "bucleBorrar:"

            "cmp %%rcx , %%rax;" //compara p<tam

            "jle finBorrar;"
            "movb $0 , (%%rdi);" //(dirDest)=0
            "inc %%rdi;"
            "inc %%rcx;"
            "jmp bucleBorrar;"

      "finBorrar:"
        :
        : "m" (imgD),"m" (w), "m" (h)
        : "%rdi", "%rbx", "%rax","%rcx", "memory"

    );

}

void imageprocess::invertir(uchar * imgO, uchar * imgD, int w, int h)
{
    /*dirOrig = imgO;
    dirDest = imgD;
    tam = w*hPara(p=0; p<tam; p++)
    {
        [dirDest] = 255-[dirOrig];
        dirOrig++;
        dirDest++;
    }*/

    asm volatile(
        "movq %0 , %%rdi;" //Carga la imagen origen
        "movq %1 , %%rsi;"  //Carga la imagen destino
        "movsxd %2 , %%rax;" //Carga w
        "movsxd %3 , %%rbx;" //Carga h
        "imul %%rax,%%rbx;" //tam = w*h
        "mov $0 , %%rcx;" //P = 0

        "bucleInvertir:"

                "cmp %%rcx ,%%rbx;" //p<tam
                "jle finInvertir;"
                "inc %%rcx;"
                "mov $255,%%r8 ;"
                "sub (%%rdi) ,%%r8 ;"
                "mov %%r8, (%%rsi);"
                "inc %%rdi;"
                "inc %%rsi;"
                "jmp bucleInvertir;"

           "finInvertir:"

        :
        : "m" (imgO),	"m" (imgD), "m" (w), "m" (h)
        : "%rdi","%rsi", "%rax", "%rbx","%rcx","%r8", "memory"
    );

}

void imageprocess::umbralizar(uchar * imgD, int w, int h)
{

   /* dirDest = imgD;
    tam = w*h
    Para(p=0; p<tam; p++)
    {
        Si([dirDest]>128)
                [dirDest] = 255;
        Sino
                [dirDest] = 0;
        dirDest++;}
    */
    asm volatile(
        "movq %0 , %%rdi;" //Cargamos la imagen destino
        "movsxd %1, %%rax;" //Cargamos w
        "movsxd %2, %%rbx;" //Cargamos h
        "imul %%rbx, %%rax;" // tam = w*h
        "mov $0, %%rcx;" // P = 0
        "mov $0, %%r8;"

         "bucleUmbralizar:"
                "cmp %%rcx, %%rax;" //p<tam
                "jle finUmbralizar;" //Salta si termina el for
                "inc %%rcx;"
                "movb (%%rdi), %%r8b;"
                "cmp $128,%%r8;"
                "jge blanco;"
                "movb $0,(%%rdi);" //Cambia a negro
                "jmp repetirBucle;"

                "blanco:"
                "movb $255,(%%rdi);" //Cambia a blanco

                "repetirBucle:"
                "inc %%rdi;"
                "jmp bucleUmbralizar;" //Vuelva al inicio del bucle




          "finUmbralizar:"

        :
        : "m" (imgD), "m" (w), "m" (h)
        : "%rdi", "%rcx", "%rbx", "%rax","%r8","memory"

    );
}

void imageprocess::eliminarRuido_F1(uchar * imgO, uchar * imgD, int w, int h)
{
    asm volatile(
       "movq %0,%%rsi;" //Cargamos ImgO
        "movq %1,%%rdi;" //Cargamos ImgD
        "mov $1,%%r8;" //f=1
        "movsxd %3,%%rax;" //Cargamos h
        "dec %%rax;"
        "movsxd %2,%%rbx;" //w
        "mov %%rbx,%%rcx;"  //w  2
        "dec %%rcx;" //w-1

  "PrimeroFor:"
         "cmp %%rax,%%r8;" //
         "jge finfinfin;"

         "mov $1,%%r9;" //c

   "SegundoFor:"
          "cmp %%rcx,%%r9;"
          "jge PrimeroForinc;"
          "movq $-1,%%r10;" //df = -1
          "mov $1,%%rdx;" //tBlancos = true;

   "PrimerWhile:"
           "cmp $1,%%r10;"
           "jg finWhile;"
           "cmpb $1, %%dl;"
           "jne finWhile;"
           "movq $-1,%%r11;" //dc = -1
    "SegundoWhile:"
           "cmp $1,%%r11;"
           "jg incrementardf;"
           "cmpb $1,%%dl;"
           "jne incrementardf;"

           "mov %%r8,%%r12;"
           "add %%r10,%%r12;"
           "imul %%rbx,%%r12;"
           "add %%r9,%%r12;"
           "add %%r11,%%r12;"

           "cmpb $0,(%%rsi,%%r12);"
           "jne jump1;"
            "movb $0,%%dl;"



           "jump1:"
                "inc %%r11;"
                "jmp SegundoWhile;"

           "incrementardf:"
                "inc %%r10;"
                "jmp PrimerWhile;"




    "finWhile:"

          "mov %%r8,%%r12;"
          "imul %%rbx,%%r12;"
          "add %%r9,%%r12;"

           "cmpb $1,%%dl;"
            "jne sino;"
            "movb $255,(%%rdi,%%r12);"
            "inc %%r9;"
            "jmp SegundoFor;"

        "sino:"
             "movb $0,(%%rdi,%%r12);"
             "inc %%r9;"
             "jmp SegundoFor;"

        "PrimeroForinc:"
                  "inc %%r8;"
                  "jmp PrimeroFor;"


 "finfinfin:"

        :
        : "m" (imgO),	"m" (imgD), "m" (w), "m" (h)
        :"%rax","%rbx","%rdx","%rsi","%rdi","%r8","%r9","%r10","%r11","%r12","%r13", "memory"
    );

}

void imageprocess::eliminarRuido_F2(uchar * imgO, uchar * imgD, int w, int h)
{
    asm volatile(
             "movq %0,%%rsi;" //Cargamos ImgO
                "movq %1,%%rdi;" //Cargamos ImgD
                "mov $1,%%r8;" //f=1
                "movsxd %3,%%rax;" //Cargamos h
                "dec %%rax;"
                "movsxd %2,%%rbx;" //w

                "mov %%rbx,%%rcx;"  //w  2
                "dec %%rcx;" //w-1
          "PrimeroFor2:"
                 "cmp %%rax,%%r8;"
                 "jge finfinfin2;"

                 "mov $1,%%r9;" //c

           "SegundoFor2:"
                  "cmp %%rcx,%%r9;"
                  "jge PrimeroFor2inc;"
                  "movq $-1,%%r10;" //df = -1
                  "mov $0,%%rdx;" //tBlancos = true;

           "PrimerWhile2:"
                   "cmp $1,%%r10;"
                   "jg finWhile2;"
                   "cmpb $0, %%dl;"
                   "jne finWhile2;"
                   "movq $-1,%%r11;" //dc = -1
          "SegundoWhile2:"
                   "cmp $1,%%r11;"
                   "jg incrementardf2;"
                   "cmpb $0,%%dl;"
                   "jne incrementardf2;"


                   "mov %%r8,%%r12;"
                   "add %%r10,%%r12;"
                   "imul %%rbx,%%r12;"
                   "add %%r9,%%r12;"
                   "add %%r11,%%r12;"


                   "cmpb $255,(%%rsi,%%r12);"
                   "jne jump12;"
                    "movb $1,%%dl;"



                   "jump12:"
                        "inc %%r11;"
                        "jmp SegundoWhile2;"

                   "incrementardf2:"
                        "inc %%r10;"
                        "jmp PrimerWhile2;"




            "finWhile2:"

                   "mov %%r8,%%r12;"
                   "imul %%rbx,%%r12;"
                   "add %%r9,%%r12;"

                   "cmpb $1,%%dl;"
                    "jne sino2;"
                    "movb $255,(%%rdi,%%r12);"
                    "inc %%r9;"
                    "jmp SegundoFor2;"

                "sino2:"
                     "movb $0,(%%rdi,%%r12);"
                     "inc %%r9;"
                     "jmp SegundoFor2;"


         "PrimeroFor2inc:"
                "inc %%r8;"
                "jmp PrimeroFor2;"


         "finfinfin2:"


        :
        : "m" (imgO),	"m" (imgD), "m" (w), "m" (h)
        :"%rax","%rbx","%rdx","%rsi","%rdi","%r8","%r9","%r10","%r11","%r12","%r13", "memory"
    );

}


int imageprocess::detectarV_min(uchar *imgD, int U){

    //Modifica la variable local “min”, cuyo valor es retornado
    //por el procedimiento
   /* dirDest = imgD;
    f = 0;
    cont = 0;
    Mientras(f<100 y cont<=U)
    {
        cont = 0;
        Para(c=0; c<320; c++)
        {
            Si([dirDest]==255)
                    cont++;
            dirDest++;
        }
        f++
    }
    min = f-1;
    */

    int min=0;

    asm volatile(
        "movq %1, %%rsi;" //Cargamos la imagen destino
        "movsxd %2, %%rdx;" //Cargamos el entero U
        "mov $0,%%rbx;" // f = 0;
        "mov $0, %%rcx;" // cont = 0;




        "bucleGeneralVMin:" //Mientras(f<100 y cont<=U)
             "cmp $100 , %%rbx;" //compara f<100
             "jge bucleFinVMin;"
             "cmp %%rdx,%%rcx;" //compara cont <= U
             "jg bucleFinVMin;"
             "mov $0, %%rcx;" //cont =0
             "mov $0, %%r8;" //c=0;
             "inc %%rbx;" //f++

          "bucleVMin:"

                "cmp $320, %%r8d;"
                "jge bucleGeneralVMin;"
                "inc %%r8;"
                "movb (%%rsi), %%r9b;"
                "cmpb $255, %%r9b;" //(dirDest)==255
                "jne aumentar;"
                "inc %%rcx;"//cont++
          "aumentar:"
                "inc %%rsi;" //dirDest ++
                "jmp bucleVMin;"






         "bucleFinVMin:"
                "dec %%ebx;"  //min = f-1;
                "mov %%ebx,%0;"

        : "=m" (min)
        : "m" (imgD), "m" (U)
        : "%rsi" ,"%rcx","%rbx","%rdi","%rdx","%r8","%r9","memory"
	);


    return min;
}

int imageprocess::detectarV_max(uchar *imgD, int U){

    //Modifica la variable local “max”, cuyo valor es retornado
    //por el procedimiento
    /*dirDest = imgD + 320*100-1;
    f = 99;
    cont = 0;
    Mientras(f>=0 y cont<=U)
    {
        cont = 0;
        Para(c=0; c<320; c++)
        {
            Si([dirDest]==255)
                    cont++;
            dirDest--;
        }
        f--
    }
    max = f+1;
    */

    int max=0;

    asm volatile(

                "movq %1, %%rsi;" //Cargamos la imagen destino
                "mov $100 , %%rax;"
                "imul $320 ,%%rax;"
                "dec %%rax;"
                "add %%rax,%%rsi;"
                "movsxd %2, %%rdx;" //Cargamos el entero U
                "mov $99,%%rbx;" // f = 99;
                "mov $0, %%rcx;" // cont = 0;




                "bucleGeneralVMax:" //Mientras(f>=0 y cont<=U)
                     "cmp $0, %%rbx;" //compara f>=0
                     "jl bucleFinVMax;"
                     "cmp %%rdx,%%rcx;" //compara cont <= U
                     "jg bucleFinVMax;"


                     "mov $0, %%rcx;" //cont = 0
                     "mov $0, %%r8;" //c=0;
                     "dec %%rbx;" //f--
                "bucleVMax:"

                      "cmp $320, %%r8;"   //Para(c=0; c<320; c++)
                      "jge bucleGeneralVMax;"
                      "inc %%r8;"  //c++
                      "movb (%%rsi), %%r9b;"
                      "cmpb $255, %%r9b;"
                      "jne disminuir;"
                      "inc %%rcx;"
                "disminuir:"
                      "dec %%rsi;" //dirDest--
                      "jmp bucleVMax;"




             "bucleFinVMax:"
                     "inc %%ebx;"
                     "mov %%ebx,%0;" //max = f+1


        : "=m" (max)
        : "m" (imgD), "m" (U)
        : "%rsi" ,"%rax","%rcx","%rbx","%rdi","%rdx","%r8","%r9","memory"
    );

    return max;

}


void imageprocess::detectarH_F1(uchar *imgD, uchar * VA, uchar U){


    /*dirVA = VA;
    Para(c=0; c<320; c++)
    {
        dirDest = imgD;
        cont = 0;
        Para(f=0; f<100; f++)
        {
            Si([dirDest+c]==255)
                    cont++;
            dirDest = dirDest+320;
        }
        Si(cont>U)
                [dirVA+c] = 1;
        Sino
                [dirVA+c] = 0;
    }*/
    asm volatile(
        "movq %1, %%rdi;" //Cargamos VA
        "mov $0, %%rcx;" //c =0
        "movb %2, %%al;" //Cargamos u

           "bucleDetectarF1:"
                "cmp $320, %%rcx;"
                "jge FinFin;"
                "movq %0,%%rsi;" //Cargamos imagenDestino
                "mov $0, %%r8;" //cont = 0
                "mov $0, %%r9;" //f=0

           "bucle2DetectarF1:"

                "cmp $100, %%r9;"  //Para(f=0; f<100; f++)
                "jge Condicion;"

                "movb (%%rsi,%%rcx),%%r10b;"
                "cmpb $255,%%r10b;" //Si([dirDest+c]==255)
                "jne bucle3;"
                "inc %%r8;" //cont ++

            "bucle3:"
                "add $320,%%rsi;" //dirDest = dirDest+320;
                "inc %%r9;"//f++
                "jmp bucle2DetectarF1;"





            "Condicion:"
                "cmp %%rax, %%r8;" //Si(cont>U)
                "jle Opcion1;"
                "movb $1, (%%rdi,%%rcx);"
                "jmp Tercerbucle;"

            "Opcion1:"
                "movb $0, (%%rdi,%%rcx);"
                "jmp Tercerbucle;"

            "Tercerbucle:"
                "inc %%rcx;"
                "jmp bucleDetectarF1;"

        "FinFin:"
        :
        : "m" (imgD), "m" (VA),"m" (U)
        : "%rsi","%rdi","%rax","%rcx","%rdx","%r8","%r9","%r10","memory"
	);

}

void imageprocess::detectarH_F2(uchar * VA, int * Vh){
    /*
    dirVA = VA;
    dirVh = Vh;
    c = 0;
    nC = 0;
    Mientras(c<320 y nC<7)
    {
        :"%rsi","%rdi","%rax","%rbx","%rcx","%r8","%r9","%rdx","%r10","%r11","memory"

        Si([dirVA+c] == 1)
        {
            iC = c;
            iC++;
            Mientras(iC<320 y [dirVA+iC] == 1)
                    iC++;
            tamC = iC-c;
            [dirVh] = c + tamC/2;
            dirVh = dirVh+4;
            nC++;
            c = iC-1;
        }
        c++
    }*/

    asm volatile(
        "movq %0,%%rsi;" //Va
        "movq %1,%%rdi;" //Vh
        "mov $0,%%rcx;" //c = 0;
        "mov $0,%%rbx;" //nC= 0;



         "BucleMientrasHF2:"
               "cmp $320,%%rcx;"
               "jge finHF2;"
               "cmp $7,%%rbx;"  //mientras(c<320 y nC<7)
               "jge finHF2;"

               "movb (%%rsi,%%rcx),%%r8b;"
               "cmpb $1 , %%r8b;"   //si ((dirVa+c)==1)
               "jne BucleInc;"
               "mov %%rcx,%%rdx;"// iC=c
               "inc %%rdx;"

          "BucleMientras2:"
                "cmp $320,%%rdx;"
                "jge siguiente;"
                "movb (%%rsi,%%rdx),%%r9b;" //Mientras(iC<320 y [dirVA+iC] == 1)
                "cmpb $1,%%r9b;"
                "jne siguiente;"

                "inc %%rdx;" //iC++
                "jmp BucleMientras2;"

          "siguiente:"
                "mov %%rdx,%%rax;"
                "sub %%rcx,%%rax;" //tam = iC-c
                "shr $1,%%rax;" //  tam/2
                "add %%rcx,%%rax;" //c+tamC/2
                "mov %%rax,(%%rdi);" //[dirVh] = c + tamC/2;
                "add $4,%%rdi;" //dirVh + 4

                "inc %%rbx;" //nC++
                "dec %%rdx;"
                "mov %%rdx,%%rcx;" //c=iC-1

           "BucleInc:"
                "inc %%rcx;" //c++
                "jmp BucleMientrasHF2;" //Vuelve al bucle


         "finHF2:"



        :
        : "m" (VA),"m"(Vh)
        :"%rsi","%rdi","%rax","%rbx","%rcx","%r8","%r9","%rdx","memory"
    );

}


void imageprocess::recortar(uchar *imgO, uchar *imgD,int x, int y, int w, int h){
/*
    dirOrig = imgO + 320*y+x;
    dirDest = imgD;
    Para(f=0; f<h; f++)
    {
        Para(c=0; c<w; c++)
        {
            [dirDest] = [dirOrig]
            dirDest++;
            dirOrig++
        }
        dirOrig = dirOrig + 320 - w;
    }*/

	asm volatile(
        "movq %0,%%rsi;" //Cargamos imgO
        "movq %1,%%rdi;" //Cargamos imgD
        "movsxd %2,%%rax;" //Cargamos x
        "movsxd %3,%%rbx;" //Cargamos y
        "movsxd %4,%%rcx;" //Cargamos w
        "movsxd %5,%%rdx;" //Cargamos h
        "imul $320,%%rbx;" //320*y
        "add %%rax,%%rbx;" //320*y+x
        "add %%rbx,%%rsi;" //320*y+x+ImgO

        "mov $0,%%r8;" // f=0

      "Para:"
            "cmp %%rdx,%%r8;" //Para(f=0; f<h; f++)
            "jge finRecortar;"
            "inc %%r8;" //f++
            "mov $0,%%r9;" //c=0

       "Para2:"
            "cmp %%rcx,%%r9;" //Para(c=0; c<w; c++)
            "jge reinicio;"
            "inc %%r9;" //c++
            "movb (%%rsi),%%r10b;"
            "movb %%r10b,(%%rdi);" //[dirDest] = [dirOrig]

            "inc %%rdi;" //dirDest++
            "inc %%rsi;" //dirOrig++
            "jmp Para2;"

      "reinicio:"
            "add $320,%%rsi;"
            "sub %%rcx,%%rsi;"  //dirOrig = dirOrig +320-w
            "jmp Para;"

      "finRecortar:"


        :
        : "m" (imgO),"m"(imgD),"m" (x),"m" (y),"m" (w),"m"(h)
        : "%rsi","%rdi","%rax","%rbx","%rcx","%rdx","%r8","%r9","%r10","memory"
    );

}

int imageprocess::matching(uchar *caracM, uchar *patrones[31], int ini, int tam){
    int iMax=0;
  /*  //Modifica la variable local “iMax”, cuyo valor es retornado
    //por el procedimiento
    dirPatrones = patronesiP = ini;
    maxSim = -1000
            Para(nP=0; nP<tam; nP++)
    {
        posPatron = iP*8;
        dirP = [dirPatrones + posPatron];
        dirCarac = caracM;
        sim = 0;
        Para(p=0; p < 32*55; p++)
        {
            Si([dirCarac] == [dirP])
            {
                Si([dirCarac] = 255)
                        sim = sim+3;
                Sinosim = sim+1;
            }
            Sinosim = sim-1;
            dirCarac++;
            dirP++;
        }
        Si(sim>maxSim)
        {
            maxSim = sim;
            iMax = iP;
        }
        iP++;
    }
}
*/

    asm volatile(
        "movq %2,%%rsi;" //Cargamos patrones
        "movsxd %3,%%rax;"//ip= ini
        "movsxd %4,%%rbx;"// cargamos tam
        "movq $-1000,%%r8;"// maxSim=-1000
        "mov $0,%%rcx;"  //np=0
       "bucleFor1:"
                "cmp %%rbx,%%rcx;" //Para(nP=0; nP<tam; nP++)
                "jge finMatching;"
                "inc %%rcx;" //nP++
                "mov %%rax,%%r9;"
                "imul $8,%%r9;" //posPatron = iP*8;
                "mov (%%rsi,%%r9),%%rdx;" //dirP = [dirPatrones + posPatron];
                "movq %1,%%rdi;" //Cargamos carac
                "mov %0,%%r10;" //sim = 0
                "mov $32,%%r11;"
                "imul $55,%%r11;" // 32*55
                "mov $0,%%r12;" //p=0
        "bucleFor2:"

                "cmp %%r11,%%r12;"
                "jge salto3;"
                "inc %%r12;"
                "movb (%%rdi),%%r13b;"
                "movb (%%rdx),%%r14b;"
                "cmpb %%r13b,%%r14b;"
                "jne salto1;"
                "cmpb $255,(%%rdi);"
                "jne salto2;"
                "add $3,%%r10;"
                "jmp salto4;"
       "salto2:"
                "inc %%r10;"
                "jmp salto4;"


       "salto1:"
                "dec %%r10;" //sim=sim-1
       "salto4:"
                "inc %%rdi;" //dircac++
                "inc %%rdx;" //dirp++
                "jmp bucleFor2;" //Vuelve al segundo for
       "salto3:"
                "cmp %%r10,%%r8;" //Si(sim>maxSim)
                "jge incremento;"
                "mov %%r10,%%r8;" //maxSim = sim
                "mov %%eax,%0;" //devuelve la variable local iMax=iP



       "incremento:"

                "inc %%rax;" //incrementa iP
                "jmp bucleFor1;"

       "finMatching:"



        : "=m" (iMax)
        : "m" (caracM),"m"(patrones),"m" (ini),"m" (tam)
        : "%rdi","%rsi","%rax","%rbx","%rdx","%rcx","%r8","%r9","%r10","%r11","%r12","%r13","%r14","memory"
    );

    return iMax;
}
