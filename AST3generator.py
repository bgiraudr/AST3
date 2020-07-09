"""
Programme de création de niveau pour A Switch to the top fait par Tituya
Pour le CPC#26
"""

import pygame
from pygame.locals import *

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

"""
s="10001011111011111111111111000101dd10001111dddd11110000101dd100010000000000011111m1dd1aaa1000ccccddd110s00010013331000000000011dddd110010001000dd00000100000000010e01000dd00000011111100011111dddddddd1111k000000010000111001111111111111101000000000111111000010000100000000000000010K010000100011100000011110t0100001000111000ddd1111000101111101111111111111"
grille=[]
for j in range(14):
    grille.append([])
    for i in range(25):
        grille[-1].append(s[i+25*j])"""

p = open("src/set.c","w+")
p.write("#include \"setlevel.h\"\n#include <gint/std/string.h>\nvoid set_level(int id_level, char level[], int *startx, int *starty, char *gravity, char check_coin){\nswitch(id_level){")


#Defini la suite des blocs pendant les changements (cliquer sur un 1 va donner un 2, cliquer sur un 11 un 0...)
suite=["0","1","d","s","e","k","3","K","a","c","m","t"]

def place():
    level = font.render(str(id_level),1,(0,0,0))
    levelgr = font.render(str(gravityid),1,(0,0,0))
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
    fenetre.blit(level, (10, 10))
    fenetre.blit(levelgr, (10, 60))
    pygame.display.flip()

pygame.init()
pygame.display.set_caption('AST3 generator (Tituya)')
fenetre = pygame.display.set_mode((25*52, 14*52))
font = pygame.font.SysFont('arial',25,True)

id_level = 1
gravity = ""
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

for a in range(14):
    for b in range(25):
        pygame.draw.rect(fenetre,(255,255,255),((52*b, 52*a), (52, 52)))
place()
securite=False
while securite==False:
    #boucle permettant l'affichage
    for event in pygame.event.get():
        if event.type==QUIT:
            securite=True
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_TAB:
                p.write(f"case {id_level}:\nmemcpy(level,\""+str(grille).replace("]","").replace("(","").replace(")","").replace("'","").replace("[","").replace(" ","").replace(",","")+"\",350);\nbreak;\n")
                gravity+=f"case {id_level}:\n*default_gravity = {gravityid};\nbreak;\n"
                id_level+=1
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
                p.write("}if(check_coin) for (int i = 0; level[i]!='\\0' ; i++) if(level[i]=='t') level[i]='0';\nset_gravity(id_level, gravity);\nunsigned int x = 0;\
\nunsigned int y = 0;\nunsigned int i = 0;\nwhile (i!=strlen(level)){\nswitch(level[i]){\ncase 's':\n*startx = x;\n*starty = y;\nbreak;}\nx+=16;\nif(x==16*25){x=0;\ny+=16;}i++;}}\n\
void set_gravity(int id_level, char *default_gravity){\nswitch(id_level){\n"+gravity+"}}")
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