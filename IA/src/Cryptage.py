import os


class ChiffreMsg:
    def generate_key(msg, key):
        if len(msg) == len(key):
            return key
        else:
            key_extended = key * (len(msg) // len(key)) + key[:len(msg) % len(key)]
            return key_extended

    def crypte_vigneron(msg, key):
        key = generate_key(msg, key)
        addition_res = 0
        encrypted_msg = ""
        for i in range(len(msg)):
            addition_res = 0
            addition_res = ord(msg[i]) + ord(key[i])
            if (addition_res > 127):
                addition_res -= 127
            encrypted_msg += chr(addition_res)
        return encrypted_msg


    def decrypte_vigneron(msg_crypte, key):
        key = generate_key(msg_crypte, key)
        decrypted_msg = ""
        for i in range(len(msg_crypte)):
            subtraction_res = ord(msg_crypte[i]) - ord(key[i])
            if subtraction_res < 0:
                subtraction_res += 127
            decrypted_msg += chr(subtraction_res)
        return decrypted_msg


    def check_msg(key, msg_crypte, pid_liste):
        decrypte_msg = decrypte_vigneron(msg_crypte, key)
        nouvelle_chaine = decrypte_msg[len(pid_liste):]
        for i in range(len(pid_liste)):
            if (decrypte_msg[:len(pid_liste[i][0])] == pid_liste[i][0] and
             nouvelle_chaine[:len(pid_liste[i][1])] == pid_liste[i][1]):
                return True
        return False

def main():
    pid_liste = []
    pid = os.getpid()
    chiffre = ChiffreMsg
    id = 0
    id += 1
    pid_liste.append((pid, id))
    msg = input("ICI MSG: ")
    key =  input("ICI KEY: ")
    msg_crypte = chiffre.crypte_vigneron(msg, key)
    if (chiffre.check_msg(key, msg_crypte, pid_liste) == False):
        return False
    print("msg crypte= ", msg_crypte)
    decrypte_msg = chiffre.decrypte_vigneron(msg_crypte, key)
    print(decrypte_msg)
    return True

main()

