from sklearn import linear_model


def model(gdp, freedom, outputs):
    # Creează matricea independentelor, care include coloanele PIB-ului pe cap de locuitor și libertatea
    x = [[el1, el2] for el1, el2 in zip(gdp, freedom)]

    # Creează un obiect de regresie liniară și îl potrivește cu datele de intrare și ieșire
    regressor = linear_model.LinearRegression()
    regressor.fit(x, outputs)

    # Extrage coeficienții de interceptare și de înclinare din modelul învățat
    w0, w1, w2 = regressor.intercept_, regressor.coef_[0], regressor.coef_[1]

    # Afișează modelul învățat, care este o funcție pătratică de forma f(x) = w2 * x^2 + w1 * x + w0
    print('The learnt model: f(x) = ', w2, ' * x^2 + ', w1, ' * x + ', w0)
