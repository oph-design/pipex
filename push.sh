#!/bin/bash
DATE=$(date +"%Y-%m-%d %T")
REPO=https://github.com/oph-design/pipex.git
git add .
git commit -m" $(echo $DATE)"
git push $REPO
