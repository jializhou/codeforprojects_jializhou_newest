'''
Created on Sep 5, 2014

@author: I311161
'''
import csv
import collections


tailnums={}
output = open("tailnum_itinerary1.txt", "w")
with open('tailnum_delay1.csv', 'r') as f1:
    tailnum_data = csv.reader(f1)
    for row in tailnum_data:
        if row[4] not in tailnums:
            tailnums[row[4]]=collections.Counter()
        tailnums[row[4]][row[6]+' '+row[7]]+=1  
    for key, count in tailnums.items():
        output.write('tailnum: %s\n'%(key))
        output.write('itinerary : cnt\n')
        for count_key in count.most_common(10):
            output.write('%s : %d\n'%(count_key[0],count_key[1]))
f1.close()
output.close()
            
            
        