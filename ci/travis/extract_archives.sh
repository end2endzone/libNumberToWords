# Any commands which fail will cause the shell script to exit immediately
set -e

# Validate Travis CI environment
if [ "$TRAVIS_BUILD_DIR" = "" ]; then
  echo "Please define 'TRAVIS_BUILD_DIR' environment variable.";
  exit 1;
fi

echo ============================================================================
echo Extracting French archive...
echo ============================================================================
cd $TRAVIS_BUILD_DIR/test/test_files
sudo apt-get update
sudo apt-get install p7zip-full p7zip p7zip-rar
7z x french.zip
