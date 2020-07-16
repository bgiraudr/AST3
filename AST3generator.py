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

newgrille()

def load(ids):
    global grille
    for lev,ide in niv.items():
        if lev==ids:
            grille=[]
            print(ide)
            for j in range(14):
                grille.append([])
                for i in range(25):
                    grille[-1].append(str(ide[i+25*j]))
            place()
            break

niv={}
niveau=1
texte = open("src/setlevel.c", "r+")
for line in texte:
    if "memcpy" in line:
        niv[niveau]=line[14:-8]
        niveau+=1
    if "del_level" in line:
        break

p = open("editor/setlevel.c","w+")
p.write("#include \"setlevel.h\"\n#include <gint/std/string.h>\nvoid set_level(int id_level, char level[], int *startx, int *starty, char *gravity, char check_coin){\nswitch(id_level){")


#Defini la suite des blocs pendant les changements (cliquer sur un 1 va donner un 2, cliquer sur un 11 un 0...)
suite=["0","1","d","s","e","k","3","K","a","c","m","t","l","b"]

def place():
    level = font.render(str(id_level),1,(0,0,0))
    levelgr = font.render(str(gravityid),1,(0,0,0))
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

id_level = 1
gravity = ""
identifiant = ""
gravityid = 0

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

for cle in niv:
    if id_level==cle:
        load(id_level)
        break
    else:
        newgrille()
place()
securite=False
while securite==False:
    clock.tick(60)
    for event in pygame.event.get():
        if event.type==QUIT:
            securite=True
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_TAB:
                identifiant+=f"case {id_level}:\nmemcpy(level,\""+str(grille).replace("]","").replace("(","").replace(")","").replace("'","").replace("[","").replace(" ","").replace(",","")+"\",350);\nbreak;\n"
                gravity+=f"case {id_level}:\n*default_gravity = {gravityid};\nbreak;\n"
                id_level+=1
                for cle in niv:
                    if id_level==cle:
                        load(id_level)
                        break
                    else:
                        newgrille()
                place()
            if event.key == pygame.K_LSHIFT:
                if gravityid:
                    gravityid=0
                else:
                    gravityid=1
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
                p.write(identifiant+"}if(check_coin) for (int i = 0; level[i]!='\\0' ; i++) if(level[i]=='t') level[i]='0';\nset_gravity(id_level, gravity);\nunsigned int x = 0;\
\nunsigned int y = 0;\nunsigned int i = 0;\nwhile (i!=strlen(level)){\nswitch(level[i]){\ncase 's':\n*startx = x;\n*starty = y;\nbreak;}\nx+=16;\nif(x==16*25){x=0;\ny+=16;}i++;}}\n\
void set_gravity(int id_level, char *default_gravity){\nswitch(id_level){\n"+gravity+"}}\nvoid del_level(char level[])\n{memcpy(level,\"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\",350);}")
                securite=True
                texte.close()
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