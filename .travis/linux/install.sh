docker build -t bornagain/focal -f `dirname $0`/Dockerfile .
docker run --security-opt seccomp=unconfined -d --name dd -it bornagain/focal
docker ps -a

