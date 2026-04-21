@echo off

pushd build
call ct.exe
popd

pushd tools
call view.py
popd
