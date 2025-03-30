
# RADIO-REVEIL

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
![Image](https://github.com/user-attachments/assets/4093da03-631c-43b5-b6fe-094922fafef0)
## Schéma de principe 
![Image](https://github.com/user-attachments/assets/4d5a33f2-1d60-49ca-8ec1-a10d4f81cbbe)
##  Ordinogramme
![Image](https://github.com/user-attachments/assets/f3433281-d999-4199-b0b5-efa0e48044cc)
##  PCB 
-  PCB Vue Complète
![Image](https://github.com/user-attachments/assets/966f4ecb-5f1b-4d91-85ef-e5b77afcab6d)
![Image](https://github.com/user-attachments/assets/8fe2e0ab-96f2-44cb-8530-3971c6b6dd52)

-  PCB Vue Sans Sérigraphie
  ![Image](https://github.com/user-attachments/assets/47664c8e-1043-4bdc-9638-84d3fb8ab6df)
