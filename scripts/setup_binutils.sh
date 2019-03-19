NAME_BREW="binutils"
NAME_LINUX_LIB1="binutils"
NAME_LINUX_LIB2="binutils"

OS=`uname`

LOG_CLEAR='\033[2K'
LOG_RED='\033[1;31m'
LOG_GREEN='\033[1;32m'
LOG_BLUE='\033[1;34m'
LOG_VIOLET='\033[1;35m'
LOG_NOCOLOR='\033[0m'
X='x'
V='✓'

TITLE=$LOG_CLEAR$LOG_BLUE
TITLE_MSG="setup $NAME_BREW"
END=$LOG_NOCOLOR

SETUP=--$LOG_CLEAR$LOG_GREEN$V$LOG_NOCOLOR'\t'setup\ .....................\ $LOG_VIOLET
KO=--$LOG_CLEAR$LOG_RED$X$LOG_NOCOLOR'\t'setup\ .....................\ $LOG_VIOLET
KO_MSG="Please check and install manually"


if [ "$OS" = 'Darwin' ]
	then
	if !(brew ls --versions $NAME_BREW > /dev/null)
	then
		echo -e $TITLE$TITLE_MSG$END
		echo -e $SETUP$NAME$END
		brew update
		brew install $NAME_BREW
	fi
elif [ "$OS" = 'Linux' ]
	then
	if !(dpkg -s $NAME_LINUX_LIB1 > /dev/null)
	then
		echo -e $TITLE$TITLE_MSG$END
		echo -e $SETUP$NAME$END
		sudo apt-get update
		sudo apt-get install --yes $NAME_LINUX_LIB1
	fi
	if !(dpkg -s $NAME_LINUX_LIB2 > /dev/null)
	then
		echo -e $TITLE$TITLE_MSG$END
		echo -e $SETUP$NAME$END
		sudo apt-get update
		sudo apt-get install --yes $NAME_LINUX_LIB2
	fi
else
	echo -e $TITLE$TITLE_MSG$END
	echo -e $KO$NAME$END'\t'$KO_MSG
fi
