# Run this script from the home directory to install lua in the proper directory for the ConfigurationReader program
curl -R -O http://www.lua.org/ftp/lua-5.3.4.tar.gz
tar zxf lua-5.3.4.tar.gz
cd lua-5.3.4
sudo apt-get install libreadline-dev
make linux test
sudo make linux install