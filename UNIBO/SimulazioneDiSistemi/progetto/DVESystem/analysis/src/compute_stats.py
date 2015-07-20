'''
@author: Fabio Biselli


'''

import sys
import csv
from math import sqrt

BATCH = 180

def main(args):
    x_bar = []
    
    # Compute mean
    print('\n-----------------------------')
    print('Tempo di risposta del server.')
    print('-----------------------------')
    for current in range(1, BATCH + 1):
        responseFile = 'responses-' + str(current) + '.csv'
        respReader = csv.reader(open('../data/' + responseFile), delimiter = ',')
        x_bar_i = 0
        n = 0
        for row in respReader:
            if row[0] != 'time':
                if float(row[0]) > 20.0 and float(row[0]) < 180.0:
                    x_bar_i += float(row[1])
                    n += 1
        x_bar.append(x_bar_i / n)
    mu = 0
    for x_i in x_bar:
        mu += x_i / BATCH
    print('Stima puntuale della media: ' + str(mu))
    
    sigma2 = 0
    for x_i in x_bar:
        sigma2 += (x_i - mu)**2
    sigma2 /= (BATCH - 1)
    print('Varianza campionaria: ' + str(sigma2))
    
    a = mu - 1.96 * (sqrt(sigma2) / sqrt(BATCH))
    b = mu + 1.96 * (sqrt(sigma2) / sqrt(BATCH))
    print('Intervallo di confidenza: (' + str(a) + ', ' + str(b) + ')')
    
    # Compute mean
    print('\n-----------------------------')
    print('Presence factor.')
    print('-----------------------------')
    for current in range(1, BATCH + 1):
        responseFile = 'presence-' + str(current) + '.csv'
        respReader = csv.reader(open('../data/' + responseFile), delimiter = ',')
        x_bar_i = 0
        n = 0
        for row in respReader:
            if row[0] != 'time':
                x_bar_i += float(row[1])
                n += 1
        x_bar.append(x_bar_i / n)
    mu = 0
    for x_i in x_bar:
        mu += x_i / BATCH
    print('Stima puntuale della media: ' + str(mu))
    
    sigma2 = 0
    for x_i in x_bar:
        sigma2 += (x_i - mu)**2 / (BATCH - 1)
    print('Varianza campionaria: ' + str(sigma2))
    
    a = mu - 1.96 * (sqrt(sigma2) / sqrt(BATCH))
    b = mu + 1.96 * (sqrt(sigma2) / sqrt(BATCH))
    print('Intervallo di confidenza: (' + str(a) + ', ' + str(b) + ')')
    
if __name__ == '__main__':
    main(sys.argv[1:])
