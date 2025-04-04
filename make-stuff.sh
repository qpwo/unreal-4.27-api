

cp-path() {
  if [ $# -ne 2 ]; then
    echo "Usage: cp-path source destination"
    return 1
  fi

  local source="$1"
  local dest="$2/$1"

  # Check if source exists
  if [ ! -e "$source" ]; then
    echo "Error: Source '$source' does not exist"
    return 1
  fi

  # Create the destination directory structure
  mkdir -p "$(dirname "$dest")"

  # Remove destination if it already exists
  if [ -e "$dest" ]; then
    rm -rf "$dest"
  fi

  # Copy the source to the destination
  if [ -d "$source" ]; then
    cp -r "$source" "$(dirname "$dest")"
  else
    cp "$source" "$dest"
  fi

  echo "Copied '$source' to '$dest'"
}

cd ~/ue4/Engine/Source
rm -rf ~/tmp/ue4-public-headers
mkdir ~/tmp/ue4-public-headers
for x in $(find . -type f \( -name "*.h" -o -name "*.hpp" \) -printf "%h\n" | sort -u | grep -v ThirdParty | grep -v Private | grep -v Internal | grep -v Android | grep -v Windows | grep -v IOS | grep -v TVOS | grep -v Mac | grep -v LinuxArm64 | grep -v generated | grep Public); do
    echo x is $x
    cp-path $x ~/tmp/ue4-public-headers
done


cd ~/tmp/ue4-public-headers
rm -vf $(fd -e cpp -e json . ~/tmp/ue4-public-headers)
rm -rvf $(fd IOS)
rm -rvf $(fd Android)
rm -rvf $(fd '^Windows$')
rm -rvf $(fd 'TVOS')
rm -rvf $(fd '^Mac$')
rm -rvf $(fd '^LinuxArm64$')
rm -rvf $(fd 'Private')
rm -rvf $(fd 'ThirdParty')
rm -rvf $(fd 'Internal')
# Remove empty directories
find . -type d -empty -delete
