
import tensorflow as tf
from tensorflow.keras.models import Model
from tensorflow.keras.layers import Dense, Flatten, Conv2D, MaxPooling2D
from tensorflow.keras.datasets import mnist
from sklearn.ensemble import AdaBoostClassifier
from sklearn.tree import DecisionTreeClassifier 
from sklearn.model_selection import train_test_split,KFold, cross_val_score
from sklearn.metrics import accuracy_score
import numpy as np


#ADA Boost


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

# def create_model():
#     model = Sequential([
#         Dense(128, activation='relu', input_shape=(X_train.shape[1],)),
#         Dense(64, activation='relu'),
#         Dense(10, activation='softmax')  # Output layer for classification
#     ])
#     model.compile(optimizer=Adam(), loss='sparse_categorical_crossentropy', metrics=['accuracy'])
#     return model


# X_train = X_train.reshape((X_train.shape[0], -1)) / 255.0
# X_test = X_test.reshape((X_test.shape[0], -1)) / 255.0

# Set up K-Fold Cross-Validation
k = 5  # Number of folds
kf = KFold(n_splits=k, shuffle=True, random_state=42)

accuracy_per_fold = []

# K-Fold Cross-Validation
for fold, (train_index, val_index) in enumerate(kf.split(X_train)):
    print(f'Fold {fold + 1}')
    
    # Split the data into training and validation sets for this fold
    X_train_fold, X_val_fold = X_train[train_index], X_train[val_index]
    y_train_fold, y_val_fold = Y_train[train_index], Y_train[val_index]
    
    # Create a new instance of the model for each fold
    model = create_cnn()
    
    # Train the model on the training fold
    model.fit(X_train_fold, y_train_fold, epochs=5, batch_size=32, verbose=0)
    
    # Evaluate the model on the validation fold
    val_predictions = np.argmax(model.predict(X_val_fold), axis=1)
    accuracy = accuracy_score(y_val_fold, val_predictions)
    
    # Store the accuracy for this fold
    accuracy_per_fold.append(accuracy)
    print(f'Accuracy for fold {fold + 1}: {accuracy * 100:.2f}%')

# Calculate the average accuracy across all folds
average_accuracy = np.mean(accuracy_per_fold)
print(f'\nAverage Accuracy Across {k} Folds: {average_accuracy * 100:.2f}%')