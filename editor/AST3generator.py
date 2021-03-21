# coding: utf-8

import pygame
from pygame.locals import *

clock = pygame.time.Clock()

def newgrille():
    global grille
    grille=\
    ["1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1"],\
    ["1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"],\
    ["1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"],\
    ["1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"],\
    ["1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"],\
    ["1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"],\
    ["1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"],\
    ["1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"],\
    ["1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"],\
    ["1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"],\
    ["1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"],\
    ["1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"],\
    ["1","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","1"],\
    ["1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1","1"]

def load(ids):
    global grille, gravityid, app, disa
    try:
        lv = open(f"editor/levels/{ids}.lvl","r")
        ide = lv.readlines()
        gravityid=str(ide[0][350:])
        if len(ide)==1:
            ide = str(ide[0][:-1])
        else:
            if ide[1]!="\n":
                app = int(ide[1][:-1])
                disa = int(ide[2])
            else:
                app = int(ide[2][:-1])
                disa = int(ide[3])
            ide = str(ide[0][:-2])
        grille=[]
        for j in range(14):
            grille.append([])
            for i in range(25):
                grille[-1].append(str(ide[i+25*j]))
    except FileNotFoundError:
        newgrille()
        gravityid="6"
    place()

def place():
    level = font.render(str(id_level),1,(0,0,0))
    if int(gravityid)==6: levelgr = font.render("↓",1,(120,0,0))
    if int(gravityid)==7: levelgr = font.render("↑",1,(0,120,120))
    timeapp = font.render("A="+str(app),1,(255,230,0))
    timedisa = font.render("D="+str(disa)+"    LOCK : "+str(lock),1,(255,180,0))
    for a in range(14):
        for b in range(25):
            pygame.draw.rect(fenetre,(255,255,255),((52*b, 52*a), (52, 52)))
    for a in range(14):
        for b in range(25):
            if grille[a][b]=="0":
                pygame.draw.rect(fenetre,(255,255,255),((52*b, 52*a), (52, 52)))
            if grille[a][b]=="1":
                fenetre.blit(pygame.transform.scale(solid_0,(52,52)),(52*b,52*a))
            if grille[a][b]=="s" and int(gravityid)==6:
                fenetre.blit(pygame.transform.scale(player.subsurface((0,0),(12,12)),(39,39)),(52*b,52*a+13))
            elif grille[a][b]=="s" and int(gravityid)==7:
                fenetre.blit(pygame.transform.scale(player.subsurface((0,0),(12,12)),(39,39)),(52*b,52*a))
            if grille[a][b]=="e":
                fenetre.blit(pygame.transform.scale(end,(52,52)),(52*b,52*a))
            if grille[a][b]=="d":
                fenetre.blit(pygame.transform.scale(dead,(52,52)),(52*b,52*a))
            if grille[a][b]=="k":
                fenetre.blit(pygame.transform.scale(key1,(52,52)),(52*b,52*a))
            if grille[a][b]=="c":
                fenetre.blit(pygame.transform.scale(chrono1,(52,52)),(52*b,52*a))
            if grille[a][b]=="3":
                fenetre.blit(pygame.transform.scale(keyblock,(52,52)),(52*b,52*a))
            if grille[a][b]=="m" and tab==0:
                fenetre.blit(pygame.transform.scale(chrono2appear,(52,52)),(52*b,52*a))
            elif grille[a][b]=="m" and tab:
                fenetre.blit(pygame.transform.scale(chrono2,(52,52)),(52*b,52*a))
            if grille[a][b]=="K":
                fenetre.blit(pygame.transform.scale(key2,(52,52)),(52*b,52*a))
            if grille[a][b]=="a" and tab==0:
                fenetre.blit(pygame.transform.scale(key2blockvoid,(52,52)),(52*b,52*a))
            elif grille[a][b]=="a" and tab:
                fenetre.blit(pygame.transform.scale(key2block,(52,52)),(52*b,52*a))
            if grille[a][b]=="t":
                fenetre.blit(pygame.transform.scale(coin,(52,52)),(52*b,52*a))
            if grille[a][b]=="l":
                fenetre.blit(pygame.transform.scale(chock,(52,52)),(52*b,52*a))
            if grille[a][b]=="b":
                fenetre.blit(pygame.transform.scale(blackout,(52,52)),(52*b,52*a))
            if grille[a][b]=="B":
                fenetre.blit(pygame.transform.scale(damaged,(52,52)),(52*b,52*a))
            if grille[a][b]=="i":
                fenetre.blit(pygame.transform.scale(ice,(52,52)),(52*b,52*a))
            if grille[a][b]=="S":
                fenetre.blit(pygame.transform.scale(switch,(52,52)),(52*b,52*a))
            if grille[a][b]=="h" and tab==0:
                fenetre.blit(pygame.transform.scale(appear,(52,52)),(52*b,52*a))
            elif grille[a][b]=="h" and tab:
                fenetre.blit(pygame.transform.scale(appearblock,(52,52)),(52*b,52*a))
    fenetre.blit(level, (10, 10))
    fenetre.blit(levelgr, (10, 60))
    fenetre.blit(timeapp, (55, 10))
    fenetre.blit(timedisa, (140, 10))
    if id_level==0 : fenetre.blit(font.render("NIVEAU DE TEST",1,(0,180,255)), (600,10))
    pygame.display.flip()

def write():
    f = open(f"editor/levels/{id_level}.lvl","w+")
    if not "c" in str(grille): 
        if not "m" in str(grille): 
            f.write(str(grille).replace("]","").replace("(","").replace(")","").replace("'","").replace("[","").replace(" ","").replace(",","")+f"{gravityid}")
        else: f.write(str(grille).replace("]","").replace("(","").replace(")","").replace("'","").replace("[","").replace(" ","").replace(",","")+f"{gravityid}\n{app}\n{disa}")
    else: f.write(str(grille).replace("]","").replace("(","").replace(")","").replace("'","").replace("[","").replace(" ","").replace(",","")+f"{gravityid}\n{app}\n{disa}")
    f.close()

pygame.init()
pygame.mixer.quit()
pygame.display.set_caption('AST3 generator (Tituya)')
fenetre = pygame.display.set_mode((25*52, 14*52))
font = pygame.font.SysFont('arial',25,True)

#Defini la suite des blocs pendant les changements (cliquer sur un 1 va donner un 2...)
suite=["0","1","d","s","e","k","3","K","a","c","m","t","l","b","B","i","S","h"]

lvm = open(f"include/define.h","r")
id_level = 0
gravityid = 6
disa = 10
app = 13
lock=""
tab = 0

solid_0 = pygame.image.load("editor/img/solid_0.png").convert_alpha()
player = pygame.image.load("editor/img/player.png").convert_alpha()
keyblock = pygame.image.load("editor/img/keyblock.png").convert_alpha()
key2block = pygame.image.load("editor/img/key2block.png").convert_alpha()
key2blockvoid = pygame.image.load("editor/img/key2blockvoid.png").convert_alpha()
chrono1 = pygame.image.load("editor/img/chrono1.png").convert_alpha()
chrono2 = pygame.image.load("editor/img/chrono2.png").convert_alpha()
chrono2appear = pygame.image.load("editor/img/chrono2appear.png").convert_alpha()
key1 = pygame.image.load("editor/img/key1.png").convert_alpha()
key2 = pygame.image.load("editor/img/key2.png").convert_alpha()
end = pygame.image.load("editor/img/end.png").convert_alpha()
dead = pygame.image.load("editor/img/dead.png").convert_alpha()
coin = pygame.image.load("editor/img/coin.png").convert_alpha()
chock = pygame.image.load("editor/img/chock.png").convert_alpha()
blackout = pygame.image.load("editor/img/blackout.png").convert_alpha()
damaged = pygame.image.load("editor/img/damaged.png").convert_alpha()
switch = pygame.image.load("editor/img/switch.png").convert_alpha()
ice = pygame.image.load("editor/img/ice.png").convert_alpha()
appear = pygame.image.load("editor/img/appear.png").convert_alpha()
appearblock = pygame.image.load("editor/img/appearblock.png").convert_alpha()

load(id_level)
place()
securite=False
while securite==False:
    clock.tick(60)
    for event in pygame.event.get():
        if event.type==QUIT:
            securite=True
        elif event.type == pygame.KEYDOWN:
            carac= event.dict['unicode']
            if carac == "d":
                id_level+=1
                load(id_level)
                place()
            if carac == "q":
                if id_level!=0: id_level-=1
                load(id_level)
                place()
            if carac == "z":
                app+=1
                write()
                place()
            if carac == "s":
                app-=1
                write()
                place()
            if carac == "r":
                disa+=1
                write()
                place()
            if carac == "f":
                disa-=1
                write()
                place()
            if carac == "a":
                lock=""
                place()
            if carac == "n":
            	newgrille()
            	write()
            	place()
            if event.key == pygame.K_LSHIFT:
                if gravityid=="7":
                    gravityid="6"
                else:
                    gravityid="7"
                write()
                place()
            if event.key == pygame.K_TAB:
            	if tab==0: tab = 1
            	else: tab = 0
            	place()
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                x=int(event.pos[0]/52)
                y=int(event.pos[1]/52)
                if lock!="":
                    grille[y][x]=lock
                else:
                    for i in range(len(suite)):
                        if grille[y][x] == suite[i]:
                            if i!=len(suite)-1:
                                grille[y][x]=suite[i+1]
                                break
                            else:
                                grille[y][x]=suite[0]
                                break
                pygame.draw.rect(fenetre,(255,255,255),((52*x, 52*y), (52, 52)))
                place()
            if event.button == 2:
                x=int(event.pos[0]/52)
                y=int(event.pos[1]/52)
                for i in range(len(suite)):
                    if grille[y][x] == suite[i]:
                        lock=suite[i]
                place()
            if event.button == 3:
                x=int(event.pos[0]/52)
                y=int(event.pos[1]/52)
                grille[y][x]="0"
                pygame.draw.rect(fenetre,(255,255,255),((52*x, 52*y), (55, 55)))
                place()
            write()
