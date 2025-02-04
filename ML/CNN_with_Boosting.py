#ADA Boost

import tensorflow as tf
from tensorflow.keras.models import Model
from tensorflow.keras.layers import Dense, Flatten, Conv2D, MaxPooling2D
from tensorflow.keras.datasets import mnist
from sklearn.ensemble import AdaBoostClassifier
from sklearn.tree import DecisionTreeClassifier 
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
import numpy as np

#load mnist dataset
(X_train,Y_train),(X_test,Y_test)=mnist.load_data()

#normalize images
X_train,X_test=X_train/255.0,X_test/255.0

#expand dimensions for CNN input
X_train=np.expand_dims(X_train,axis=-1)
X_test=np.expand_dims(X_test,axis=-1)

#Build a simple CNN model
def create_cnn():
    model=tf.keras.Sequential([
        Conv2D(32,(3,3),activation="relu",input_shape=(28,28,1)),
        MaxPooling2D((2,2)),
        Flatten(),
        Dense(128,activation='relu'),
        Dense(10,activation='softmax') #10 classes for MNIST
    ])
    model.compile(optimizer='adam',loss='sparse_categorical_crossentropy',metrics=['accuracy'])
    return model
cnn_model=create_cnn()
cnn_model.fit(X_train,Y_train,epochs=3,batch_size=64,validation_data=(X_test,Y_test))

#Extract deep features from CNN(using the second last layer)
feature_extractor= Model(inputs=cnn_model.inputs,outputs=cnn_model.layers[-2].output)
X_train_features=feature_extractor.predict(X_train)
X_test_features=feature_extractor.predict(X_test)

#Train Adaoost on CNN features
boosting_model=AdaBoostClassifier(DecisionTreeClassifier(max_depth=1),n_estimators=50)
boosting_model.fit(X_train_features,Y_train)

#make predictions
Y_pred=boosting_model.predict(X_test_features)

#Evaluate performance
print(f"Boosted Model Accuracy:{accuracy_score(Y_test,Y_pred)}")
