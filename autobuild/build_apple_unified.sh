#!/bin/bash

project_dir=../solutions/mac/BrainCloudCpp.xcodeproj
solution_dir=../solutions/mac
artifacts_dir=artifacts
config=Release

#temporary to switch to the beta xcode
#export DEVELOPER_DIR=/Applications/Xcode-beta.app/Contents/Developer

if [ "$config" == "Release" ]
then
  build_config=Release
fi

library_os="Apple_C++"

build_version="$1"
if [ "$build_version" == "" ]
then
  echo "build_apple_unified.sh <build_version>"
  echo ""
  echo "Must set build_version via 4 digit number"
  echo " ie \"1.6.0.1234\""
  exit 1
fi

build_internal_version=`echo $build_version | cut -d \".\" -f 4`
build_external_version=`echo $build_version | cut -d \".\" -f 1-3`


function failed()
{
    local error=${1:-Undefined error}
    echo "Failed: $error" >&2
    exit 1
}

function build_app()
{
  local devired_data_path="$HOME/Library/Developer/Xcode/DerivedData"

  #get the name of the workspace to be build, used as the prefix of the DerivedData directory for this build
  #local workspace_name=$(echo "$workspace" | sed -n 's/\([^\.]\{1,\}\)\.xcworkspace/\1/p')
  #build the app
  echo "Running xcodebuild > xcodebuild_output ..."

  rm -rf tmp
  mkdir tmp
  
  output_folder_ios="`xcodebuild -project $project_dir -scheme "BrainCloudSDK-iOS" -sdk "iphoneos" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "BrainCloudSDK-iOS" -sdk "iphoneos" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi
  mv "$output_folder_ios/libBrainCloudClient-iOS.a" "tmp/libBrainCloud_ios.a"

  output_folder_ios_sim="`xcodebuild -project $project_dir -scheme "BrainCloudSDK-iOS" ARCHS=x86_64 -sdk "iphonesimulator" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "BrainCloudSDK-iOS" ARCHS="i386 x86_64" -sdk "iphonesimulator" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi
  mv "$output_folder_ios_sim/libBrainCloudClient-iOS.a" "tmp/libBrainCloud_iossim.a"


  # tvos arm/sim
  output_folder_tvos="`xcodebuild -project $project_dir -scheme "BrainCloudSDK-tvOS" ENABLE_BITCODE=YES -sdk "appletvos" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "BrainCloudSDK-tvOS" -sdk "appletvos" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi
  mv "$output_folder_tvos/libBrainCloudClient-tvOS.a" "tmp/libBrainCloud_tvos.a"

  output_folder_tvos_sim="`xcodebuild -project $project_dir -scheme "BrainCloudSDK-tvOS" ARCHS=x86_64 ENABLE_BITCODE=YES -sdk "appletvsimulator" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "BrainCloudSDK-tvOS" ARCHS=x86_64 -sdk "appletvsimulator" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi
  mv "$output_folder_tvos_sim/libBrainCloudClient-tvOS.a" "tmp/libBrainCloud_tvossim.a"


  # mac osx
  output_folder_osx="`xcodebuild -project $project_dir -scheme "BrainCloudSDK-OSX" -sdk "macosx" -showBuildSettings | grep " BUILT_PRODUCTS_DIR" |cut -d "=" -f 2 | tr -d " "`"
  xcodebuild -verbose -project $project_dir -scheme "BrainCloudSDK-OSX" -sdk "macosx" -configuration "$build_config" clean build 
  if [ $? -ne 0 ]
  then
    failed xcodebuild
  fi

  rm -rf brainCloud
  mkdir brainCloud
  mkdir -p brainCloud/include/braincloud
  mkdir brainCloud/libs
  mkdir brainCloud/src
  mkdir brainCloud/thirdparty

  # create fat binaries
  lipo -create "tmp/libBrainCloud_ios.a" "tmp/libBrainCloud_iossim.a" -output brainCloud/libs/brainCloudClient_ios.a
  lipo -create "tmp/libBrainCloud_tvos.a" "tmp/libBrainCloud_tvossim.a" -output brainCloud/libs/brainCloudClient_tvos.a
  cp "$output_folder_osx/libBrainCloudClient-OSX.a" brainCloud/libs/brainCloudClient_osx.a

  cp ../include/braincloud/*.h brainCloud/include/braincloud

  # copy in the thirdparty dependencies
  cp -r ../lib/jsoncpp-1.0.0 brainCloud/thirdparty
  cp -r ../lib/mac/curl brainCloud/thirdparty
  cp -r ../lib/mac/openssl brainCloud/thirdparty

  cp docs/README.TXT brainCloud

  zip -r $artifacts_dir/brainCloudClient_${library_os}_${build_version}.zip brainCloud

  rm -rf brainCloud
}

function clean_artifacts
{
  rm -rf $artifacts_dir
  mkdir $artifacts_dir
}

# turn on shell command logging
set -x

# turn on exit on fail 
set -e

# turn on fail if something in pipeline fails
set -o pipefail

echo "**** Clean artifacts"
clean_artifacts
echo
echo "**** Build"
build_app
echo
echo "**** Complete!"

