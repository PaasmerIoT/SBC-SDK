#!/bin/bash

path=`pwd`

cat > .Install.log << EOF3
Logfile for Installing Paasmer...

EOF3
RANDOM=$$
echo $path >> .Install.log
user=$(echo $USER)
user='/home/'$user
echo $user >> .Install.log

echo "--> Installing...\n";
sudo chmod -R 777 ./*


echo "--> Installing requerments....."

sudo apt-get update >> .Install.log
sudo apt-get install -y python2.7 libssl-dev python-pip >> .Install.log
sudo apt-get install -y python-dev >> .Install.log
sudo apt-get install -y xterm >> .Install.log
#cd ~

sudo pip install awscli
echo "Configuring data..."

sudo mkdir -p /root/.aws
sudo chmod 777 /root/.aws
cat > /root/.aws/config << EOF1
[default]
region = us-west-2
EOF1

accesskey=$(echo "U2FsdGVkX1904GIBR/J1JHaexBsYkU151ON7m0qqDvXHZP8OsLxZRH7zETfqopS6tB/bVMUfYJHBzkPQ/67R2g==" | openssl enc -aes-128-cbc -a -d -salt -pass pass:asdfghjkl);

keyid=$(echo "U2FsdGVkX19XbOtwglyiBxjyEME74FjnlS5KrbdvXHQGbUC/BulYsgg+a35BR64W" | openssl enc -aes-128-cbc -a -d -salt -pass pass:asdfghjkl);


echo "[default]
aws_secret_access_key = $accesskey
aws_access_key_id = $keyid
" > /root/.aws/credentials

sudo tar -xf wiringPi.tar -C ../
sudo chmod -R 777 ../../*
sudo tar -xf subscribe_publish_sample.tar -C $path/samples/linux/

mac=$(ifconfig | grep 'HWaddr' |awk '{print $5}' | head -n 1)
echo "#define MAC \"$mac\"" > $path/samples/linux/subscribe_publish_sample/mac.h


echo "-----BEGIN CERTIFICATE-----
MIIE0zCCA7ugAwIBAgIQGNrRniZ96LtKIVjNzGs7SjANBgkqhkiG9w0BAQUFADCB
yjELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQL
ExZWZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJp
U2lnbiwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxW
ZXJpU2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0
aG9yaXR5IC0gRzUwHhcNMDYxMTA4MDAwMDAwWhcNMzYwNzE2MjM1OTU5WjCByjEL
MAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQLExZW
ZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJpU2ln
biwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxWZXJp
U2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9y
aXR5IC0gRzUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvJAgIKXo1
nmAMqudLO07cfLw8RRy7K+D+KQL5VwijZIUVJ/XxrcgxiV0i6CqqpkKzj/i5Vbex
t0uz/o9+B1fs70PbZmIVYc9gDaTY3vjgw2IIPVQT60nKWVSFJuUrjxuf6/WhkcIz
SdhDY2pSS9KP6HBRTdGJaXvHcPaz3BJ023tdS1bTlr8Vd6Gw9KIl8q8ckmcY5fQG
BO+QueQA5N06tRn/Arr0PO7gi+s3i+z016zy9vA9r911kTMZHRxAy3QkGSGT2RT+
rCpSx4/VBEnkjWNHiDxpg8v+R70rfk/Fla4OndTRQ8Bnc+MUCH7lP59zuDMKz10/
NIeWiu5T6CUVAgMBAAGjgbIwga8wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8E
BAMCAQYwbQYIKwYBBQUHAQwEYTBfoV2gWzBZMFcwVRYJaW1hZ2UvZ2lmMCEwHzAH
BgUrDgMCGgQUj+XTGoasjY5rw8+AatRIGCx7GS4wJRYjaHR0cDovL2xvZ28udmVy
aXNpZ24uY29tL3ZzbG9nby5naWYwHQYDVR0OBBYEFH/TZafC3ey78DAJ80M5+gKv
MzEzMA0GCSqGSIb3DQEBBQUAA4IBAQCTJEowX2LP2BqYLz3q3JktvXf2pXkiOOzE
p6B4Eq1iDkVwZMXnl2YtmAl+X6/WzChl8gGqCBpH3vn5fJJaCGkgDdk+bW48DW7Y
5gaRQBi5+MHt39tBquCWIMnNZBU4gcmU7qKEKQsTb47bDN0lAtukixlE0kF6BWlK
WE9gyn6CagsCqiUXObXbf+eEZSqVir2G3l6BFoMtEMze/aiCKm0oHw0LxOXnGiYZ
4fQRbxC1lfznQgUy286dUV4otp6F01vvpX1FQHKOtw5rDgb7MzVIcbidJ4vEZV8N
hnacRHr2lVz2XTIIM6RUthg/aFzyQkqFOFSDX9HoLPKsEdao7WNq
-----END CERTIFICATE-----
" > $path/certs/rootCA.crt

touch $path/certs/output.txt
sudo aws iot create-keys-and-certificate --set-as-active --certificate-pem-outfile $path/certs/e76b102a41-certificate.pem.crt --public-key-outfile $path/certs/e76b102a41-public.pem.key --private-key-outfile $path/certs/e76b102a41-private.pem.key > $path/certs/output.txt
sudo chmod -R 777 ./*
cat $path/certs/output.txt >> .Install.log

out=$(sudo cat $path/certs/output.txt | grep "certificateArn" | awk '{print $2}')

#ARN=$(echo "${out::-1}")
ARN=$(echo $out | sed 's/,$//')
echo $ARN >> .Install.log

no=$RANDOM
sudo aws iot create-policy --policy-name Paasmer-thing-policy-$no --policy-document '{ "Version": "2012-10-17", "Statement": [{"Action": ["iot:*"], "Resource": ["*"], "Effect": "Allow" }] }' >> .Install.log

echo "alias PAASMER='sudo aws iot attach-principal-policy --policy-name Paasmer-thing-policy-$no --principal $ARN'" >> ~/.bashrc
echo "Added to alias...\n" >> .Install.log


echo '#!/bin/bash
source ~/.bashrc;
sudo PAASMER;
sudo sed -i 's/alias PAASMER/#alias PAASMER/g' ~/.bashrc
echo "Done Installing...";' > $path/Configure.sh

sudo chmod -R 777 ./*
#sudo bash $path/Configure.sh
#echo "***********     STEP-1     ********************************"
#echo "-->  You can run simply below script "
#echo "-->  sudo ./Configure.sh "
echo "************************************************************"
echo "-----------------------------------------------------------"
echo "-->  Run below commands.."
echo "-->  1) sudo su "
echo "-->  2) source ~/.bashrc "
echo "-->  3) PAASMER "
echo "-->  4) sed -i 's/alias PAASMER/#alias PAASMER/g' ~/.bashrc "
echo "-->  5) exit "
echo "**************************************************************"

