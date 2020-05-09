# Author: Marc-Antoine Lacroix
# A chose your own adventure game (in French) that can read the choices from a .csv file
# The objective is to collect as many points as possible based off your reactions to certain events around your children
# Was used to teach myself how to use OOP under Python

import os
import time
import pandas as pd

# defining the sleep times in seconds:
s = 4
s2 = 8

class human(object):
    def __init__(self,name,love_points):
        self.love_points = love_points
        self.name = name

    def adjust_love(self,value):
        self.love_points = self.love_points + int(value)
        return self.love_points

class event(object):
    def __init__(self,name,description,choice1,choice2,choice3,
                value1,value2,value3,
                energy1,energy2,energy3,
                answer1,answer2,answer3):
        self.name = name
        self.description = description
        self.choice1 = choice1
        self.choice2 = choice2
        self.choice3 = choice3
        self.value1 = value1
        self.value2 = value2
        self.value3 = value3
        self.energy1 = energy1
        self.energy2 = energy2
        self.energy3 = energy3
        self.answer1 = answer1
        self.answer2 = answer2
        self.answer3 = answer3
    
    def get_value(self):
        enter = input("Fais ton choix! (1,2 ou 3):")
        os.system('clear')
        if enter == '1':
            print("\nTu as choisi:  {}\n".format(self.choice1))
            print("\n{}\n".format(self.answer1))
            return self.value1, self.energy1
        if enter == '2':
            print("\nTu as choisi:  {}\n".format(self.choice2))
            print("\n{}\n".format(self.answer2))
            return self.value2, self.energy2
        if enter == '3':
            print("\nTu as choisi:  {}".format(self.choice3))
            print("\n{}\n".format(self.answer3))
            return self.value3, self.energy3
        else:
            print("no valid number")

def create_objects():
    df = pd.read_csv('game_data.csv',sep=';')
    objs = list()
    for index,row in df.iterrows():
        objs.append(event(row['name'],row['description'],row['choice1'],row['choice2'],row['choice3'],
                    row['value1'],row['value2'],row['value3'],
                    row['energy1'],row['energy2'],row['energy3'],
                    row['answer1'],row['answer2'],row['answer3']))
    return objs

def start_game():
    print("""
    Le jeu consiste a repondre a une serie de questions choix-reponses. Sophie, John et Marc-Antoine
    feront des folies, des choses droles et moins droles. Tu dois choisir tes reactions et actions. Si 
    les enfants sont contents, ils gagneront des points d'amour. S'ils ne sont pas contents, ils en 
    perdront.
    
    Attention ! Tu n'as pas d'energie illimitee. Certaines actions te couteront plus d'energie que 
    d'autres. Il faut donc faire attention a ce que tu fais, sinon le jeu est termine !
    L'objectif est d'aller chercher le maximum de points d'amour chez Sophie et John. 
    
    Bonne chance!
    """)
    start = input("Lorsque tu es prete a debuter, entres le mot 'ok': ")
    if start != 'ok':
        input('Appuies sur "ok"')

def quit(name,objs):
# to quit the game
    a = input("Veux-tu quitter le jeu? (oui/non)".format(name))
    if a == 'oui':
        os.system('clear')
        exit()
    elif a == 'non':
        run_game(objs)
    else:
        print("oui ou non?")
        quit(name,objs)

def event_selection(objs,i):
    print('{} \n'.format(objs[i].description))
    print('1 -> {} \n'.format(objs[i].choice1))
    print('2 -> {} \n'.format(objs[i].choice2))
    print('3 -> {} \n'.format(objs[i].choice3))
    points,energy = objs[i].get_value()
    return points,energy

def print_status(points1,points2,name,points3):
    print("####### John a {} points d'amour #######".format(points1))
    print("#######    Sophie a {} points d'amour  #######\n".format(points2))
    print("### {} a {} points d'energie ###\n".format(name,points3))

def run_game(objs):
# game loop
    os.system('clear')
    i = 0
    Sophie = human('Sophie',0)
    John = human('John',0)
    Mom = human('Mom',15)
    print('\nBienvenue {}! Bonne chance!'.format(Mom.name))
    time.sleep(s)
    os.system('clear')
    while i < len(objs):
        print_status(John.love_points,Sophie.love_points,Mom.name,Mom.love_points)
        if Mom.love_points <= 0:
            print("Tu n'as plus d'energie!")
            time.sleep(s)
            break
        points,energy = event_selection(objs,i)
        if objs[i].name == 'Sophie':
            if points < 0:
                print("\nSophie perd {} points d'amour!".format(points))
            if points >= 0:
                print("Sophie gagne {} points d'amour!\n".format(points))
            if energy < 0:
                print("Tu perds {} points d'energie!".format(energy))
            if energy >= 0:
                print("Tu gagnes {} points d'energie!".format(energy))
            Sophie.adjust_love(points)
            Mom.adjust_love(energy) 
            print("\nSophie a maintenant: {} points d'amour".format(Sophie.love_points))
            print("Tu as maintenant: {} points d'energie".format(Mom.love_points))
        if objs[i].name == 'John':
            if points < 0:
                print("\nJohn perd {} points d'amour!".format(points))
            if points >= 0:
                print("John gagne {} points d'amour!\n".format(points))
            if energy < 0:
                print("Tu perds {} points d'energie!".format(energy))
            if energy > 0:
                print("Tu gagnes {} points d'energie!".format(energy))
            if energy == 0:
                print("Tu ne gagnes ni perds de points d'energie!")
            John.adjust_love(points)
            Mom.adjust_love(energy) 
            print("\nJohn a maintenant: {} points d'amour".format(John.love_points))
            print("Tu as maintenant: {} points d'energie".format(Mom.love_points))
        if objs[i].name == 'John_Sophie':
            if points < 0:
                print("\nJohn & Sophie perdent {} points d'amour!".format(points))
            if points >= 0:
                print("John & Sophie gagnent {} points d'amour!\n".format(points))
            if energy < 0:
                print("Tu perds {} points d'energie!".format(energy))
            if energy > 0:
                print("Tu gagnes {} points d'energie!".format(energy))
            if energy == 0:
                print("Tu ne gagnes ni perds de points d'energie!")
            John.adjust_love(points)
            Sophie.adjust_love(points)
            Mom.adjust_love(energy) 
            print("\nJohn a maintenant: {} points d'amour".format(John.love_points))
            print("Sophie a maintenant: {} points d'amour".format(John.love_points))
            print("Tu as maintenant: {} points d'energie".format(Mom.love_points))
        time.sleep(s2)
        os.system('clear')
        i += 1
    print("Le jeu est fini! John a {} points d'amour et Sophie {} points d'amour!".format(John.love_points,Sophie.love_points))
    time.sleep(s2)
    quit(Mom.name,objs)

def main():
    print("\nBienvenue a jeu de la famille Lacroix!")
    time.sleep(s)
    os.system('clear')
    objs = create_objects()
    start_game()
    while True:
        run_game(objs)

if __name__ == '__main__':
    main()