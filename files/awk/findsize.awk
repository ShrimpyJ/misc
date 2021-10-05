ls -R -al 2> /dev/null | awk '/\.js$/ {printf("%-48s %8s\n", $9, $5); n += $5} END {printf("\nTotal: %.2f MB\n", n/1000000);}'
