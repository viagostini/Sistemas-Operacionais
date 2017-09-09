for i in `seq 1 90`; do
    sort -g unsorted_trace_file_$i.txt > trace_file_$i.txt
    rm unsorted_trace_file_$i.txt
done

