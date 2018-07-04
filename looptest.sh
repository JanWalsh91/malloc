echo $1
echo $2

testNumber=$1
if [ -z "$testNumber" ]; then
	testNumber=0
fi

loopCount=$2
if [ -z "$loopCount" ]; then
	loopCount=10
fi

for run in $(seq 1 $loopCount)
do
	echo "======== iteration: $run ========"
	if  [[ "$testNumber" -lt "6" ]]; then
		echo "./run.sh /usr/bin/time -l ./test$testNumber"
  		./run.sh /usr/bin/time -l ./test$testNumber
	else
		echo "./test$testNumber"
		./test$testNumber
	fi
done

echo "test $testNumber done $loopCount times"