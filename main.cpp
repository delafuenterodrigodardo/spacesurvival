#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
using namespace sf;
#include "clases.h"




int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(anchoPantalla, altoPantalla), "Space Survival", Style::Fullscreen);
    app.setFramerateLimit(60);

    Texture t1,t2,t3,t4,t5,t6,t7;
    t1.loadFromFile("images/spaceship3.png");
    t2.loadFromFile("images/background2.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_red.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");

    t1.setSmooth(true);
    t2.setSmooth(true);

    Sprite background(t2);

    Animacion sExplosion(t3, 0,0,256,256, 48, 0.5);
    Animacion sRock(t4, 0,0,64,64, 16, 0.2);
    Animacion sRock_small(t6, 0,0,64,64, 16, 0.2);
    Animacion sBullet(t5, 0,0,32,64, 16, 0.8);
    Animacion sPlayer(t1, 40,0,40,40, 1, 0);
    Animacion sPlayer_go(t1, 40,40,40,40, 1, 0);
    Animacion sExplosion_ship(t7, 0,0,192,192, 64, 0.5);


    std::list<Entidad*> entidades;

    for(int i=0;i<15;i++)
    {
      asteroide *a = new asteroide();
      a->settings(sRock, rand()%anchoPantalla, rand()%altoPantalla, rand()%360, 25);
      entidades.push_back(a);
    }

    player *p = new player();
    p->settings(sPlayer,200,200,0,20);
    entidades.push_back(p);

    /////main loop/////
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();

            if (event.type == Event::KeyPressed)
             if (event.key.code == Keyboard::Space)
              {
                bala *b = new bala();
                b->settings(sBullet,p->x,p->y,p->angle-10,10);
                entidades.push_back(b);

                bala *b1 = new bala();
                b1->settings(sBullet,p->x,p->y,p->angle+10,10);
                entidades.push_back(b1);

                bala *b2 = new bala();
                b2->settings(sBullet,p->x,p->y,p->angle,10);
                entidades.push_back(b2);
              }
              if (event.key.code == Keyboard::Escape){
                app.close();
              }
        }

    if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle+=3;
    if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle-=3;
    if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust=true;
    else p->thrust=false;


    for(auto a:entidades)
     for(auto b:entidades)
     {
      if (a->name=="asteroide" && b->name=="bala")
       if ( isCollide(a,b) )
           {
            a->life=false;
            b->life=false;

            Entidad *e = new Entidad();
            e->settings(sExplosion,a->x,a->y);
            e->name="explosion";
            entidades.push_back(e);


            for(int i=0;i<2;i++)
            {
             if (a->R==15) continue;
             Entidad *e = new asteroide();
             e->settings(sRock_small,a->x,a->y,rand()%360,15);
             entidades.push_back(e);
            }

           }

      if (a->name=="player" && b->name=="asteroide")
       if ( isCollide(a,b) )
           {
            if (!Keyboard::isKeyPressed(Keyboard::N)){
            b->life=false;

            Entidad *e = new Entidad();
            e->settings(sExplosion_ship,a->x,a->y);
            e->name="explosion";
            entidades.push_back(e);

            p->settings(sPlayer,anchoPantalla/2,altoPantalla/2,0,20);
            p->dx=0; p->dy=0;
            }
           }
     }


    if (p->thrust)  p->anim = sPlayer_go;
    else   p->anim = sPlayer;


    for(auto e:entidades)
     if (e->name=="explosion")
      if (e->anim.isEnd()) e->life=0;

    if (rand()%150==0)
     {
       asteroide *a = new asteroide();
       a->settings(sRock, 0,rand()%altoPantalla, rand()%360, 25);
       entidades.push_back(a);
     }

    for(auto i=entidades.begin();i!=entidades.end();)
    {
      Entidad *e = *i;

      e->update();
      e->anim.update();

      if (e->life==false) {i=entidades.erase(i); delete e;}
      else i++;
    }

   //////draw//////
   app.draw(background);
   for(auto i:entidades) i->draw(app);
   app.display();
    }

    return 0;
}
