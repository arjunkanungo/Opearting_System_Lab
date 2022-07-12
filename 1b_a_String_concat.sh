#Shell script to concatenate Two strings
#!/bin/bash
echo "Enter the First String"
read a
echo "Enter the second String"
read b
c=$a$b
echo "$c"