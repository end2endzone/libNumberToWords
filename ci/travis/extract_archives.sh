# Any commands which fail will cause the shell script to exit immediately
set -e

# Validate Travis CI environment
if [ "$TRAVIS_BUILD_DIR" = "" ]; then
  echo "Please define 'TRAVIS_BUILD_DIR' environment variable.";
  exit 1;
fi

echo ============================================================================
echo Installing 7-zip...
echo ============================================================================
sudo apt-get update
sudo apt-get install p7zip-full p7zip p7zip-rar

echo ============================================================================
echo Extracting French archive...
echo ============================================================================
cd $TRAVIS_BUILD_DIR/test/test_files
7z x -y french.zip

echo ============================================================================
echo Extracting English archive...
echo ============================================================================
cd $TRAVIS_BUILD_DIR/test/test_files
7z x -y english.zip
