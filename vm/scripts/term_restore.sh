#!/bin/sh

# Réutilise le mode RAW pour l'interception des signaux et autres
stty -raw

# Remise en place de l'echo
stty echo

# Remise en place du retour chariot
stty onlcr
