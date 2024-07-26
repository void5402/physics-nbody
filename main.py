import pygame
import copy
import random
pygame.init()
screen = pygame.display.set_mode((1000,700)) #
pygame.display.set_caption("Physics simulation.")
running = True
pm = 20e+5 #particle mass(kg)
ts = 0.1
minm=-30
maxm=30
zoom = 1
mv = 5
shade = 0
keys = []
font = pygame.font.SysFont("arial", 12)
vec = pygame.Vector2
abz = vec(screen.get_width()/2,screen.get_height()/2)
G = 6.674e-11 #the number
particles = []
screen.fill("black")
Mt = (G*pm*pm)

def partinit(pos,vector = vec(0,0), mass = pm):
    #si units> mass(kg) , position(vector), velocity(vector)
    particles.append([mass,pos,copy.copy(vector),copy.copy(vector),1])
    

def render():
    text = font.render(f"[particles: {len(particles)}, location: {abz}, zoom: {zoom}]", 0,"white")
    
    pygame.draw.circle(screen,"dark blue", abz, 80/zoom)
    pygame.draw.circle(screen,"dark red", abz, 20/zoom)
    pygame.draw.circle(screen,"dark green", abz, 1/zoom)
    screen.blit(text,(0,0))
    for obj in particles:
        pos = obj[1]/zoom + abz
        pygame.draw.circle(screen, "white", pos, obj[4])#, obj[0]/pm colision
    
    
def calculatestuff():
    for objf in particles:
        force = [0,0]
        for obj2 in particles:
            distance = obj2[1]-objf[1]
            if distance == [0,0]:
                continue
            force += (Mt/vec.magnitude(distance)**2)*vec.normalize(distance)
        objf[3]=force/pm
    for obj in particles:
        obj[2]+=obj[3]
        obj[2][0] = pygame.math.clamp(obj[2][0],-3e+8,+3e+8)#speed of light
        obj[2][1] = pygame.math.clamp(obj[2][1],-3e+8,+3e+8)
        obj[1]+=obj[2]
        
def rs(r = 0):
    if (r and not shade) or (not r and shade):
        screen.fill("black")
        
    
for l in range(150):
        partinit(vec(random.randrange(minm,maxm),random.randrange(minm,maxm)))
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEWHEEL:
            zoom += (zoom/10)*event.y*-1
            rs()
        elif event.type == pygame.KEYDOWN:
            '''
            if event.key == 119:#w
                while pygame.KEYDOWN.
                    abz[0] += 5
            elif event.key == 97:#a
                pass
            elif event.key == 115:#s
                pass
            elif event.key == 100:#d
                pass'''
            if event.key == 113:#q
                running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if event.button == 1:
                px = event.pos[0]*zoom
                py = event.pos[1]*zoom
                ax = abz[0]*zoom
                ay = abz[1]*zoom
                partinit(vec(px,py)-vec(ax,ay))
    keys = pygame.key.get_pressed()
    if keys[pygame.K_w]:
        abz[1]+=mv
        rs()
    elif keys[pygame.K_a]:
        abz[0]+=mv
        rs()
    elif keys[pygame.K_s]:
        abz[1]-=mv
        rs()
    elif keys[pygame.K_d]:
        abz[0]-=mv
        rs()
    calculatestuff()
    render()
    #print("tick")
    pygame.display.flip()
    rs(1)

pygame.quit()
