#!/bin/bash
#
# Created by Aidan Shafran
# Updated Jun 22, 2017
# WTFPL, wtfpl.net

# A list of packages to install
# Feel free to modify this
vospackages="cantarell-fonts cheese chromium dconf-editor eog gedit gnome-terminal gnome-calculator graphene-desktop libreoffice lightdm lightdm-gtk-greeter networkmanager noto-fonts paper-gtk-theme-git paper-icon-theme-git rhythmbox totem ttf-dejavu veltos-config xorg yaourt"

# Check for root
if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root." >&2
   echo "Try 'sudo ./install-veltos.sh'"
   echo ""
   exit 1
fi

bold=$(tput bold)
normal=$(tput sgr0)

echo
echo "Thank you for trying out VeltOS!"
echo
echo "------------"
echo "It is assumed you are running in a functional Arch Linux installation."
echo "------------"
echo
echo "This script will:"
echo "1) Add Velt's signing key (owned by Aidan Shafran) to pacman's keyring"
echo "2) Add VeltOS's repository to pacman's config file"
echo "3) Install all VeltOS packages and schemas"
echo "4) Enable NetworkManager (disable other network daemons first!)"
echo "5) Set lightdm-gtk-greeter's configuarion to match VeltOS themes"
echo
read -p "${bold}:: Install VeltOS? (y/n)${normal} " -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
  
  # Check for pacman
  if [ ! -f /usr/bin/pacman ]; then
    echo "pacman is not installed. Are you sure you're running Arch?" >&2
    exit 1
  fi
  if [ ! -f /usr/bin/pacman-key ]; then
    echo "pacman-key is not installed. Are you sure you're running Arch?" >&2
    exit 1
  fi
  if [ ! -f /etc/pacman.conf ]; then
    echo "You are missing /etc/pacman.conf. Are you sure you're running Arch?" >&2
    exit 1
  fi

  # Add key
  if pacman-key --init && pacman-key --keyserver pgp.mit.edu --recv-keys 1BCE8B257234A9DA2A733339C876A8F2E3BB5484 && pacman-key --lsign-key 1BCE8B257234A9DA2A733339C876A8F2E3BB5484
  then
    echo
    echo "${bold}Added Velt's signing key to keyring.${normal}"
    echo
  else
    echo
    echo "Failed to add Velt's signing key to keyring. Aborting" >&2
    exit 1
  fi
  
  if grep --quiet "\[vosrepo\]" "/etc/pacman.conf"; then
    echo "VeltOS repository already in /etc/pacman.conf"
    echo
  else
    # Append repository to /etc/pacman.conf
    # Careful to use >> to append
    echo "" >> /etc/pacman.conf
    echo "[vosrepo]" >> /etc/pacman.conf
    echo "Server = http://repo.velt.io/\$arch" >> /etc/pacman.conf
    echo "" >> /etc/pacman.conf
    echo "${bold}Added VeltOS repository to /etc/pacman.conf.${normal}"
    echo
  fi
  
  # Install packages
  if pacman --needed --quiet --noconfirm -Sy $vospackages; then 
    echo
    echo "${bold}VeltOS packages installed.${normal}"
    echo
  else
    echo
    echo "Failed to install VeltOS packages. Aborting." >&2
    exit 1
  fi

  systemctl enable NetworkManager
  echo "${bold}NetworkManager enabled.${normal}"
  echo
  
  # Init LightDM  
  if [ ! -f /etc/lightdm/lightdm-gtk-greeter.conf ]; then
    echo "Missing lightdm-gtk-greeter configuration file. Aborting." >&2
    exit 1
  fi
  
  systemctl enable lightdm
  
  # Replace #background= with the correct wallpaper, but don't change if they've already set a background
  sed -i 's/^#background=\s*$/background=\/usr\/share\/veltos\/wallpapers\/default.png/' /etc/lightdm/lightdm-gtk-greeter.conf 
  
  # Force replace theme-name, icon-theme-name, font-name, and position
  sed -i -r 's/^#?theme-name=.*$/theme-name=Paper/' /etc/lightdm/lightdm-gtk-greeter.conf
  sed -i -r 's/^#?icon-theme-name=.*$/icon-theme-name=Paper/' /etc/lightdm/lightdm-gtk-greeter.conf
  sed -i -r 's/^#?font-name=.*$/font-name=Noto Sans 10\.5/' /etc/lightdm/lightdm-gtk-greeter.conf
  sed -i -r 's/^#?position=.*$/position=30%,center 50%,center/' /etc/lightdm/lightdm-gtk-greeter.conf
  
  echo "${bold}LightDM configured.${normal}"

  echo
  echo "==========="
  echo "VeltOS successfully installed!"
  echo "==========="
  echo
  
  if [[ -z "${DISPLAY// }" ]]; then
    read -p "${bold}:: Would you like to start lightDM to login? (y/n)${normal} " -r
    if [[ $REPLY =~ ^[Yy]$ ]]; then
      systemctl start lightdm
    fi
  fi
fi
