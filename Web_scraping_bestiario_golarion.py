from selenium import webdriver
from bs4 import BeautifulSoup
import pandas as pd
import re


driver = webdriver.Chrome("C:/Users/scutt/OneDrive - studenti.unimi.it/Python/Web Scraping/chromedriver.exe")

products=[] #List to store name of the product
prices=[] #List to store price of the product
ratings=[] #List to store rating of the product
driver.get("https://golarion.altervista.org/wiki/Database_Mostri")

tableXPath='//*[@id="wiki_table_filter"]/tbody'
table=driver.find_element_by_xpath(tableXPath)

nome=[]
gs=[]
terreno=[]
clima=[]
tipo=[]
sottotipo=[]
fonte=[]

i=0
for row in table.find_elements_by_xpath('./tr'):

    tds=row.find_elements_by_xpath('./td')

    nome.append(tds[0].text)

    filterGs=re.search("(1/[1-9])|[1-9]+", tds[1].text)
    gs.append(filterGs.group(0))

    terreno.append(tds[2].text)


    if tds[3].text=="-":
        clima.append("")
    else:
        clima.append(tds[3].text)


    tipo.append(tds[4].text)

    if tds[5].text=="-":
        sottotipo.append("")
    else:
        sottotipo.append(tds[5].text)

    fonte.append(tds[6].text)

    if i%50==0:
        print('row',i)

    i+=1

driver.close()
df = pd.DataFrame({'Nome':nome,'Gs':gs, 'Terreno':terreno, 'Clima':clima, 'Tipo':tipo, 'Sottotipo':sottotipo, 'Fonte':fonte})
# df.info()
df.to_json(path_or_buf='bestiario.json', orient="table")
