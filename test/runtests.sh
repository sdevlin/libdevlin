echo "Running unit tests:"

for i in test/*_test; do
    if [ -f $i ]; then
        if $VALGRIND ./$i 2>> test/test.log; then
            echo $i PASS
        else
            echo "ERROR in test $i: here's test/test.log"
            echo "------"
            tail test/test.log
            exit 1
        fi
    fi
done

echo ""
