
# RADIO-REVEIL
<img alt="Static Badge" src="https://img.shields.io/badge/French-8A2BE2"> <img alt="Static Badge" src="https://img.shields.io/badge/Spanish-8A2BE2"> <img alt="Static Badge" src="https://img.shields.io/badge/-%20?logo=easyeda&color=blue">
![Image](https://github.com/user-attachments/assets/1f1e02f8-997e-4d4a-bef8-016fc4e9d9b0)

INTRODUCTION

Dans le cadre de mon TFE de fin d'année, mon projet consiste à concevoir un radio-réveil en appliquant les connaissances acquises au fil des années à l'Inraci.

Ce projet aura deux fonctionnalités principales :
- **Capter la radio FM**
- **Avoir un réveil fonctionnel**

De plus, il affichera l'heure et la date en temps réel grâce à un module **RTC** sur un écran **SPI**. La radio pourra changer de volume et de station grâce à **deux encodeurs rotatifs**.

L'objectif du projet est également de servir d'exemple aux nouveaux élèves de l'Inraci qui souhaitent apprendre et découvrir l'électronique à travers ce projet.

## SOMMAIRE
- [Les caractéristiques](#les-caractéristiques)
  - [Général](#général)
  - [Electronique](#electronique)
  - [Mécanique](#mécanique)
- [Schéma bloc](#schéma-bloc)
- [Schéma de principe](#schéma-de-principe)
- [Ordinogramme](#ordinogramme)
- [PCB](#Pcb)
  - [PCB Vue Complète](#Pcb-vue-complete)
  - [PCB Vue Sans Sérigraphie](#Pcb-vue-sans-serigraphie)
- [Dessin 3D](#dessin-3d)
## Caractéristiques
**Général :**
- Module RTC (PCF8523) 
- Module Radio FM (RDA5807M) 
- Écran TFT 2.8" (ILI9341) 
- Amplificateur Audio (MAX98357A) 
- Encodeur Rotatif (KY-040) 
- Fusible 
- Bouton Poussoir

**Eléctrique :**
## Antenne 
- Impedance : 75Ω
- Zone Dab ou Fm
## Récepteur Radio FM
- Sensibilité : 1.4µ - 1.8µV
- Plage de fréquence : 50 - 115 MHz
- Réception : Mono/Stéréo
- Tension d'alimentation : 2.7V - 3.3V
- Impedance : 50 Ω
- Consommation : 20mA/h
- Type de signal : Analogique
## Régulateur de Tension
- Tension d'entrée : 6.5 - 32V
- Tension de sortie : 5V
- Courant de sortie : 2A
- Rendement : 94 %
- Protection : OTP et SCP 
- Température de fonctionement : -40°C à 70 °C
## Amplificateur Audio
- Puissance de sortie : 3.2W 
- Tension d'alimentation : 2.7V - 5.5V
- Protection : OTP et OCP
- Fréquence PWM : ~300kHz
## Module RTC 
- Tension d'entrée : 3.3V ou 5V
- Précision : +~ 2sec/Jour
- Autonomie : 3ans avec pile CR1225
## Encodeur rotatif
- Tension d'alimentation : 5V
- Courant : 10 mA
- Cycle par tour : 30
## Transitor MosFet
- Tension Drain-Source : -30V
- ID=-4.2A(VGS =-10V)
- RDS(ON)＜55mΩ(VGS=-10V)
- RDS(ON)＜70mΩ(VGS=-4.5V)
- RDS(ON)＜120mΩ(VGS=-2.5V)
- Tension de commande : 2,5V - 10V
- Dissipation de puissance : 1,4W
- Vgs(th) (max.) à Id : 1,3V à 250µA
- Vgs max : +-12V

**Mécanique :**
- Materiaux : Planche de Bois Multiplex 
- Dimension : L= 15Cm , l=10Cm , Epaisseur 0.8Cm
## Schéma bloc
![Image](https://github.com/user-attachments/assets/a9f58896-cb3d-4906-8dc8-51dca3e848b4)
## Schéma de principe 
![Image](https://github.com/user-attachments/assets/4c6f0787-ac14-48d8-9e26-475951140f7d)
##  Ordinogramme
![Image](https://github.com/user-attachments/assets/04767bd1-071b-4c10-8361-5480d3212379)
##  PCB 
-  PCB Vue Complète
![Image](https://github.com/user-attachments/assets/966f4ecb-5f1b-4d91-85ef-e5b77afcab6d)
![Image](https://github.com/user-attachments/assets/8fe2e0ab-96f2-44cb-8530-3971c6b6dd52)
#
![Image](https://github.com/user-attachments/assets/124112c3-9606-4741-af46-5d660db43080)
![Image](https://github.com/user-attachments/assets/530f6ada-a466-41ef-aa7d-c0120402b4c3)

-  PCB Vue Sans Sérigraphie
  ![Image](https://github.com/user-attachments/assets/47664c8e-1043-4bdc-9638-84d3fb8ab6df)
#
![Image](https://github.com/user-attachments/assets/b3d682b8-e54c-4403-912c-ab28a95e7250)

##  Dessin 3D
![Image](https://github.com/user-attachments/assets/0c14af67-0891-4389-8921-995fe048e285)

![Image](https://github.com/user-attachments/assets/d663f5da-919d-4cfd-b1be-39fb3e78aae0)

![Image](https://github.com/user-attachments/assets/e0dbc977-80a3-46f1-9227-ad4f2b9e2fe1)

