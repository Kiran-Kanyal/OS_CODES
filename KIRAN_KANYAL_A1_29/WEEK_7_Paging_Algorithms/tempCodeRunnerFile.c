printf("Total number of Page Fault: %d",page_fault);
    printf("Page Fault Ratio: %f", (float)(page_fault)/n);
    printf("Hit Ratio: %f", (float) (n-page_fault)/n);