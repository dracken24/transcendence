set echo on

echo  "\033[32mLaunch Transcendence...\n"

# alias pushd='cd'
# alias popd='cd ..'

./Transcendence

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi

echo "\033[32m\nLaunch Transcendence done.\033[0m"
