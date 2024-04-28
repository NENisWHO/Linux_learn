#!/bin/bash

echo "It is morning? Please answer yes or no!"

read YES_OR_NO

case "$YES_OR_NO" in
    yes|y|YES|Yes)
        echo "Good morning"
        ;;
    [nN][oO])
        echo "Good afternoon"
        ;;
    *)
        echo "NOt recognized"
        ;;
esac








