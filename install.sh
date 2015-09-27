find . -name *.cc | while read File
do
  fname=`basename $File`
  name="${fname%.*}"
  echo $name
  cp ${File} ${HOME}/.vim/bundle/sonictemplate-vim/template/cpp/${name}.cpp
done

