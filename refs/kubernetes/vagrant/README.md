# GFW HOWTO

## A linux machine (host/vm) such aws ec2

- docker pull <all-kubernetes-images>
- docker save
- tar -cvzf all-k8s-images.tgz *.tar
- scp all-k8s-images.tgz user@china-vm.cn:~
- tar -xvzf all-k8s-images.tgz
- docker load -i *.tar

## Free oneline kubernetes try

- https://katacoda.com
- labs.play-with-k8s.com

I transfered successfully using the second one.
