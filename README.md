# dptf_policy
set dptf policy manually

## about
dptf - Dynamic Platform and Thermal Framework  

A auto adaptive application was developed for chromimum os and Ubuntu Linux:

https://github.com/intel/dptf

But this App cannot work on my computer, which only support passive1 policy, and on my computer use passive2 policy, so I write this simple dptf_policy to apply DPTF policy manually.

## build

- required

cmake

- download

git clone https://github.com/kaige86/dptf_policy.git

- build

cd dptf_policy  
mkdir build  
cd build  
cmake ..  
make  

## run

- show help

./dptf_policy  

- set policy

./dptf_policy passive2


