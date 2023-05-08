import os
import numpy as np
from sklearn.metrics import mean_squared_error

from sklearn_tool import regression
from developed_code import my_regression
from file import reader
from sklearn import linear_model


def main():
    crtDir = os.getcwd()
    filePath = os.path.join(crtDir, 'data', 'v3_world-happiness-report-2017.csv')

    # Încarcă datele din fișier folosind modulul reader
    # Extrage coloanele pentru PIB-ul pe cap de locuitor, Libertate și Scorul de fericire
    gdp_per_capita, freedom, outputs = reader.load_data(filePath, 'Economy..GDP.per.Capita.', 'Freedom', 'Happiness.Score')
    print('GDP per Capita: ', gdp_per_capita)
    print('Freedom: ', freedom)
    print('Outputs: ', outputs)

    # Rulează o regresie liniară folosind biblioteca sklearn și afișează rezultatele
    print('\nUsing sklearn:')
    regression.model(gdp_per_capita, freedom, outputs)
    
    # Rulează o regresie liniară folosind cod personalizat și afișează rezultatele
    print('\nUsing my code:')
    my_regression.my_linear_regression(gdp_per_capita, freedom, outputs)

    # Împarte datele într-un set de antrenare și un set de validare
    # Folosește 80% din date pentru antrenare și 20% pentru validare

    # Se utilizează 80% din date pentru antrenare pentru a permite modelului să își ajusteze 
    # coeficienții prin minimizarea erorii de antrenare și pentru a evita suprastimarea (overfitting-ul) modelului datorită unui set de antrenare prea mic.

    # Setul de validare de 20% este utilizat pentru a evalua performanța modelului pe date noi, 
    # pentru a verifica dacă modelul este capabil să generalizeze și să producă predicții precise pe date pe care nu le-a văzut în timpul antrenamentului.
    indexes = [i for i in range(len(gdp_per_capita))]
    train_sample = np.random.choice(indexes, int(0.8 * len(gdp_per_capita)), replace=False)
    validation_sample = [i for i in indexes if not i in train_sample]

    # Pregătește intrările și ieșirile de validare pentru modelul de regresie liniară
    validation_inputs = [[gdp_per_capita[i], freedom[i]] for i in validation_sample]
    validation_outputs = [outputs[i] for i in validation_sample]

    # Antrenează un model de regresie liniară pe setul de validare
    # Folosește biblioteca sklearn pentru a antrena modelul
    linear_model.LinearRegression().fit(validation_inputs, validation_outputs)
    model = linear_model.LinearRegression()
    model.fit(validation_inputs, validation_outputs)
    # Folosește modelul antrenat pentru a face predicții pe setul de validare
    computed_validation_outputs = model.predict(validation_inputs)

    # Calculează eroarea de predicție manual și folosind funcția de eroare medie pătrată din biblioteca sklearn
    error = 0.0
    for t1, t2 in zip(computed_validation_outputs, validation_outputs):
        error += (t1 - t2) ** 2
    error = error / len(validation_outputs)
    print('Prediction error (manual): ', error)

    error = mean_squared_error(computed_validation_outputs, validation_outputs)
    print('Prediction error (using sklearn):  ', error)



main()
