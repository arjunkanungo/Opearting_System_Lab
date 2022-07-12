#Shell Scipt to compare two strings
#!/bin/bash
echo "Enter String 1"
read s1
echo "Enter String 2"
read s2
if [[ "$s1" == "$s2" ]]; then
    echo "$s1 is equal to $s2"
elif [[ "$s1" < "$s2" ]]; then
    echo "$s1 is less than $s2"
else
    echo "$s1 is greater than $s2"
fi