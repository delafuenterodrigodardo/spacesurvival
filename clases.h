#ifndef CLASES_H_INCLUDED
#define CLASES_H_INCLUDED

const int anchoPantalla = 1920;
const int altoPantalla = 1080;

float GRADOSARADIANES = 0.017453f;



class Animacion
{
   public:
   float Frame, velocidad;
   Sprite sprite;
   std::vector<IntRect> cuadros;

   Animacion(){}

   Animacion (Texture &t, int x, int y, int ancho, int alto, int count, float Vel)
   {
     Frame = 0;
     velocidad = Vel;

     for (int i=0;i<count;i++)
      cuadros.push_back( IntRect(x+i*ancho, y, ancho, alto)  );

     sprite.setTexture(t);
     sprite.setOrigin(ancho/2,alto/2);
     sprite.setTextureRect(cuadros[0]);
   }


   void update()
   {
     Frame += velocidad;
     int n = cuadros.size();
     if (Frame >= n) Frame -= n;
     if (n>0) sprite.setTextureRect( cuadros[int(Frame)] );
   }

   bool isEnd()
   {
     return Frame+velocidad>=cuadros.size();
   }

};


class Entidad
{
   public:
   float x,y,dx,dy,R,angle;
   bool life;
   std::string name;
   Animacion anim;

   Entidad()
   {
     life=10;
   }

   void settings(Animacion &a,int X,int Y,float Angle=0,int radius=1)
   {
     anim = a;
     x=X; y=Y;
     angle = Angle;
     R = radius;
   }

   virtual void update(){};

   void draw(RenderWindow &app)
   {
     anim.sprite.setPosition(x,y);
     anim.sprite.setRotation(angle+90);
     app.draw(anim.sprite);

     CircleShape circle(R);
     circle.setFillColor(Color(255,0,0,170));
     circle.setPosition(x,y);
     circle.setOrigin(R,R);
     ///app.draw(circle);


   }

   virtual ~Entidad(){};
};


class asteroide: public Entidad
{
   public:

      const int variablilidad_asteroide= 4;

   asteroide()
   {
     dx=rand()%8-variablilidad_asteroide;
     dy=rand()%8-variablilidad_asteroide;
     name="asteroide";
   }

   void update()
   {
     x+=dx;
     y+=dy;

     if (x>anchoPantalla) x=0;  if (x<0) x=anchoPantalla;
     if (y>altoPantalla) y=0;  if (y<0) y=altoPantalla;
   }

};


class bala: public Entidad
{
   public:
       bool bala_erratica= true;
   bala()
   {
     name="bala";
   }

   void  update()
   {
     dx=cos(angle*GRADOSARADIANES)*6;
     dy=sin(angle*GRADOSARADIANES)*6;
     if (bala_erratica){
     angle+=rand()%7-3;  /*try this*/
     }
     x+=dx;
     y+=dy;

     if (x>anchoPantalla || x<0 || y>altoPantalla || y<0) life=0;
   }

};


class player: public Entidad
{
   public:
   bool thrust;
   int maxSpeed=15;
   int radio=2000;

   player()
   {
     name="player";
   }

   void update()
   {
     if (thrust)
      { dx+=cos(angle*GRADOSARADIANES)*0.2;
        dy+=sin(angle*GRADOSARADIANES)*0.2; }
     else
      { dx*=0.99;
        dy*=0.99; }


    float velocidad = sqrt(dx*dx+dy*dy);
    if (velocidad>maxSpeed)
     { dx *= maxSpeed/velocidad;
       dy *= maxSpeed/velocidad; }

    x+=dx;
    y+=dy;

    if (x>anchoPantalla) x=0; if (x<0) x=anchoPantalla;
    if (y>altoPantalla) y=0; if (y<0) y=altoPantalla;
   }
   int getRadio(){return radio;}

};


bool isCollide(Entidad *a,Entidad *b)
{
  return (b->x - a->x)*(b->x - a->x)+
         (b->y - a->y)*(b->y - a->y)<
         (a->R + b->R)*(a->R + b->R);
}


class Disparomejorado: public Entidad
{
   public:
   Disparomejorado()
   {
     name="Disparomejorado";
   }

   void  update()
   {
     dx=cos(angle*GRADOSARADIANES)*6;
     dy=sin(angle*GRADOSARADIANES)*6;
     // angle+=rand()%7-3;  /*try this*/
     x+=dx;
     y+=dy;

     if (x>anchoPantalla || x<0 || y>altoPantalla || y<0) life=0;
   }
};

class laser: public Entidad
{
   public:
   laser()
   {
     name="laser";
   }

   void  update()
   {
     dx=cos(angle*GRADOSARADIANES)*6;
     dy=sin(angle*GRADOSARADIANES)*6;
     // angle+=rand()%7-3;  /*try this*/
     x+=dx;
     y+=dy;

     if (x>anchoPantalla || x<0 || y>altoPantalla || y<0) life=0;
   }
};



#endif // CLASES_H_INCLUDED

