find . -name *.cc | while read File
do
  echo $File
  fname=`basename $File`
  name="${fname%.*}"
  cp $File $HOME/.vim/bundle/sonictemplate-vim/template/cpp/$name.cpp
done

