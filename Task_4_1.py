import time
import random

# We create two classes with a two way connection that implement the weapons 
# of each player and how they will affect his stats
class Gru():
    elect_prod_count = 5
    mega_magnet_count = 3
    kalman_miss_count = 1
    selec_perm_count = 2

    def __init__(self, player):
        self.player = player
        self.vector_instance = None
        self.health = 100
        self.energy = 500
        self.shield = 0

    def set_vector_instance(self, vector_instance):
        self.vector_instance = vector_instance

    def update_vector_health(self, damage, kalman = False):
        if kalman:
            self.vector_instance.health -= damage
            self.vector_instance.shield = 0
        elif self.vector_instance.shield == 0:
            self.vector_instance.health -= damage
        elif self.vector_instance.shield > 0:
            self.vector_instance.health -= (damage*(100-self.vector_instance.shield)/100)
            self.vector_instance.shield = 0
    def freeze_gun(self):
        if self.energy >= 50:
            self.energy -= 50
            self.update_vector_health(11)
        else:
            print("Freeze Gun can't be used now.")

    def electric_prod(self):
        if Gru.elect_prod_count > 0 and self.energy >= 88:
            self.energy -= 88
            self.update_vector_health(18)
            Gru.elect_prod_count -= 1
        else:
            print("Electic Prod can't be used now")

    def mega_magnet(self):
        if Gru.mega_magnet_count > 0 and self.energy >= 92:
            self.energy -= 92
            self.update_vector_health(10)
            Gru.mega_magnet_count -= 1
        else:
            print("Mega magnet can't be used now")

    def kalman_missile(self):
        if Gru.kalman_miss_count > 0 and self.energy >= 120:
            self.energy -= 120
            self.update_vector_health(20, True)
            Gru.kalman_miss_count -= 1
        else:
            print("Kalman Missile can't be used now")
    
    def barrier_gun(self):
        if self.energy >= 20:
            self.energy -= 20
            self.shield += 20
        else:
            print("Barrier Gun can't be used now")

    def selec_perm(self):
        if Gru.selec_perm_count > 0 and self.energy >= 50:
            self.shield += 50
            self.energy -= 50
            Gru.selec_perm_count -= 1
        else:
            print("Selective Permeability can't be used now")

class Vector():
    plasma_gren_count = 8
    sonic_cann_count = 3
    quantum_defl_count = 3

    def __init__(self):
        self.player = "Computer"
        self.gru_instance = None
        self.health = 100
        self.energy = 500
        self.shield = 0
        
    def set_gru_instance(self, gru_instance):
        self.gru_instance = gru_instance

    def update_gru_health(self, damage):
        if self.gru_instance.shield == 0:
            self.gru_instance.health -= damage
        else:
            self.gru_instance.health -= damage*(100-self.gru_instance.shield)/100
            self.gru_instance.shield = 0

    def laser_blasters(self):
        if self.energy >= 40:
            self.energy -= 40
            self.update_gru_health(8)
        else:
            print("Laser Blasters can's be used now")

    def plasma_grenades(self):
        if self.energy >= 56 and Vector.plasma_gren_count > 0:
            self.energy -= 56
            self.update_gru_health(13)
            Vector.plasma_gren_count -= 1
        else:
            print("Plasma Grenades can't be used now")

    def sonic_cannon(self):
        if self.energy >= 100 and Vector.sonic_cann_count > 0:
            self.energy -= 100
            self.update_gru_health(22)
            Vector.sonic_cann_count -= 1
        else:
            print("Sonic Resonance Cannon can't be used now")

    def trap_net(self):
        if self.energy >= 15:
            self.energy -= 15
            self.shield += 32
        else:
            print("Trap Net can't be used now")

    def quantum_defl(self):
        if Vector.quantum_defl_count > 0 and self.energy >= 40:
            self.energy -= 40
            self.shield += 80
            Vector.quantum_defl_count -= 1
        else:
            print("Quantum Deflector can't be used")

# We create the Game class that inherits all the methods of the above
# classes and implements them throughout the game and implements the game
# The GAme will be played in rounds where each round one player chooses
# one of his weapons and uses it until one of the player's health reaches 0
class Game(Gru, Vector):
    def __init__(self, name):
        self.name = name
        self.player_1 = Gru(name)
        self.player_2 = Vector()
    
    def get_rand_weapon(self):
        functions = [self.player_2.laser_blasters,
                      self.player_2.plasma_grenades,
                        self.player_2.sonic_cannon,
                          self.player_2.trap_net,
                            self.player_2.quantum_defl]
        random_idx = random.randint(0, len(functions)-1)
        random_function = functions[random_idx]
        random_function()
        print(f"Vector chose: {random_function.__name__}")

    def choose_weapon(self, str):
        functions = {
            "FG" : self.player_1.freeze_gun,
            "BG" : self.player_1.barrier_gun,
            "EP" : self.player_1.electric_prod,
            "KM" : self.player_1.kalman_missile,
            "MM" : self.player_1.mega_magnet,
            "SP" : self.player_1.selec_perm
        }
        return functions[str]

    def play_game(self):
        rounds = 1
        while self.player_1.health >= 0 and self.player_2.health >= 0 and self.player_1.energy >= 20 and self.player_2.energy >= 15:
            print(f"Round {rounds}")
            seconds = 3
            while seconds > 0:
                print(seconds)
                time.sleep(1)
                seconds -= 1
            print("Start")
            if rounds % 2 != 0:
                print("Gru's Turn")
                print("Here are your weapons: FG, BG, EP, KM, MM and SP")
                func = self.choose_weapon(input("Choose one of them: "))
                func()
            else:
                print("Vector's Turn")
                self.get_rand_weapon()
                
            print(f"Round {rounds} Ends.")
            print(f"Your Health: {self.player_1.health}\tVector's Health: {self.player_2.health}")
            print(f"Your Energy: {self.player_1.energy}\tVector's Energy: {self.player_2.energy}")
            rounds += 1

    def win(self):
        if self.player_2.health <= 0 or self.player_2.energy < 15:
            print("Gru wins!")
            print(f"Game Over\n{self.player_1} wins!")
        elif self.player_1.health <= 0 or self.player_1.energy < 20:
            print("Vector wins :(")
            print(f"Game Over\n{self.player_2} wins!")
            print("Hard luck next time Gru")

    def start_game(self):
        self.player_1.set_vector_instance(self.player_2)
        self.player_2.set_gru_instance(self.player_1)
        print(f"Ready Up player {self.name}\nGame about to start!")
        self.play_game() 
        self.win()

    
game1 = Game("Moustafa")
game1.start_game()
