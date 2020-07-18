"""
Programme de création de niveau pour A Switch to the top fait par Tituya
Pour le CPC#26
"""

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
    global grille, gravityid
    try:
        lv = open(f"editor/levels/{ids}.lvl","r")
        ide = lv.read()
        gravityid=ide[350:]
        ide = ide[:-1]
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
    for a in range(14):
        for b in range(25):
            pygame.draw.rect(fenetre,(255,255,255),((52*b, 52*a), (52, 52)))
    for a in range(14):
        for b in range(25):
            if grille[a][b]=="0":
                pygame.draw.rect(fenetre,(255,255,255),((52*b, 52*a), (52, 52)))
            if grille[a][b]=="1":
                fenetre.blit(pygame.transform.scale(solid_0,(52,52)),(52*b,52*a))
            if grille[a][b]=="s":
                fenetre.blit(pygame.transform.scale(player,(39,39)),(52*b,52*a+13))
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
            if grille[a][b]=="m":
                fenetre.blit(pygame.transform.scale(chrono2,(52,52)),(52*b,52*a))
            if grille[a][b]=="K":
                fenetre.blit(pygame.transform.scale(key2,(52,52)),(52*b,52*a))
            if grille[a][b]=="a":
                fenetre.blit(pygame.transform.scale(key2block,(52,52)),(52*b,52*a))
            if grille[a][b]=="t":
                fenetre.blit(pygame.transform.scale(coin,(52,52)),(52*b,52*a))
            if grille[a][b]=="l":
                fenetre.blit(pygame.transform.scale(change,(52,52)),(52*b,52*a))
            if grille[a][b]=="b":
                fenetre.blit(pygame.transform.scale(blackout,(52,52)),(52*b,52*a))
    fenetre.blit(level, (10, 10))
    fenetre.blit(levelgr, (10, 60))
    pygame.display.flip()



pygame.init()
pygame.mixer.quit()
pygame.display.set_caption('AST3 generator (Tituya)')
fenetre = pygame.display.set_mode((25*52, 14*52))
font = pygame.font.SysFont('arial',25,True)

#Defini la suite des blocs pendant les changements (cliquer sur un 1 va donner un 2, cliquer sur un 11 un 0...)
suite=["0","1","d","s","e","k","3","K","a","c","m","t","l","b"]

id_level = 1
gravityid = 6



solid_0 = pygame.image.load("editor/img/solid_0.png").convert()
player = pygame.image.load("editor/img/player.png").convert()
keyblock = pygame.image.load("editor/img/keyblock.png").convert()
key2block = pygame.image.load("editor/img/key2block.png").convert()
chrono1 = pygame.image.load("editor/img/chrono1.png").convert()
chrono2 = pygame.image.load("editor/img/chrono2.png").convert()
key1 = pygame.image.load("editor/img/key1.png").convert_alpha()
key2 = pygame.image.load("editor/img/key2.png").convert_alpha()
end = pygame.image.load("editor/img/end.png").convert_alpha()
dead = pygame.image.load("editor/img/dead.png").convert()
coin = pygame.image.load("editor/img/coin.png").convert_alpha()
change = pygame.image.load("editor/img/change.png").convert_alpha()
blackout = pygame.image.load("editor/img/blackout.png").convert_alpha()



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
                if id_level!=1: id_level-=1
                load(id_level)
                place()
            if event.key == pygame.K_LSHIFT:
                if gravityid=="7":
                    gravityid="6"
                else:
                    gravityid="7"
                f = open(f"editor/levels/{id_level}.lvl","w+")
                f.write(str(grille).replace("]","").replace("(","").replace(")","").replace("'","").replace("[","").replace(" ","").replace(",","")+f"{gravityid}")
                f.close()
                place()
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                x=int(event.pos[0]/52)
                y=int(event.pos[1]/52)
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
                securite=True
            if event.button == 3:
                x=int(event.pos[0]/52)
                y=int(event.pos[1]/52)
                for i in range(len(suite)):
                    if grille[y][x] == suite[i]:
                        if i!=len(suite)+1:
                            grille[y][x]=suite[i-1]
                            break
                        else:
                            grille[y][x]=suite[len(suite)]
                            break
                pygame.draw.rect(fenetre,(255,255,255),((52*x, 52*y), (55, 55)))
                place()
            f = open(f"editor/levels/{id_level}.lvl","w+")
            f.write(str(grille).replace("]","").replace("(","").replace(")","").replace("'","").replace("[","").replace(" ","").replace(",","")+f"{gravityid}")
            f.close()