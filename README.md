# Learn 'n' Recognize Cpp
<p style="font-size: 15px; font-style: italic;"> Version C++ </p><hr>
Détecte, analyse et compare des visages sur des images issues de différentes sources

* V0: Cette image est le résultat fonctionnel du tout premier algorithme de ma fabrication utilisant le mécanisme de Haar Cascade, basé sur les travaux de [Naotoshi Seo](http://note.sonots.com/SciSoftware/haartraining.html) :

<img src="https://github.com/blackrainb0w/Lean-n-Recognize/raw/master/testCam/proof.png">
<p style="text-align: center; font-style: italic;">Learn 'n' Recognize V0 (testCam) "proof of concept"</p>

* V1, V2 & V3: Cette image est le résultat fonctionnel de la version 3 de Learn 'n' Recognize. Cette version reprend certains principes des version 0, 1 et 2 tout en utilisant comme image d'entré un flux vidéo issue d'une webcam. Les algorithme à partir de la version 1 utilisent [LBPH (Local Binary Pattern Histogram)](http://docs.opencv.org/2.4/modules/contrib/doc/facerec/facerec_tutorial.html#local-binary-patterns-histograms). Il s'agit d'un algorithme permettant de transcrire des zones d'une image en nombres décimaux afin d'analyser des [patternes](https://www.wikiwand.com/fr/Pattern), comme des formes, permettant ainsi de discriminer les visages.

![Learn 'n' Recognize V3](https://github.com/blackrainb0w/Lean-n-Recognize/raw/master/learn_n_recognize_V3/proof.png)
<p style="text-align: center; font-style: italic;">Learn 'n' Recognize V3 "proof of concept"</p>

* V4 & V5: La version 5 allie la version 3, permettant de détecter et analyser en directe un visage, et la version 4, permettant l'apprentissage d'un visage (en l'associant à un nom), en proposant ces fonctionnalités sous formes de deux modes. Il est alors possible, d'apprendre un visage en l'associant à un nom (mode apprentissage) et ensuite de le distinguer parmis plusieurs autres visage (mode scan); le tout en une seule et unique application.

Voici un "proof of concept" en vidéo de la version 5 (cliquez sur la vignette pour ouvrir YouTube.com):

[![Learn 'n' Recognize V5 - Proof of concept](http://img.youtube.com/vi/9-2KMnhYZOk/0.jpg)](https://www.youtube.com/watch?v=9-2KMnhYZOk "Learn 'n' Recognize V5 - Proof of concept ")

* C++ V1: Cette première version en C++ est une refonte total de l'algorithme puisque il fut totalement réécris en C++. Le code source est bien plus lisible, plus facile à éditer, à améliorer, à débugger mais également à utilisé. Le programme se présente dorénavant une interface claire avec un code couleur. L'utilisateur à également la possibilité de rentrer les arguments du programme après son lancement. Le programme est maintenant divisé en plusieurs classe ayant chacune un rôle précis. La base de donnée faisant correspondre les noms des sujets à leur identifiant est maintenant sous forme de fichier SQLite. D'aitre part, puisque le C++ est un langage compilé (à l'instar du Python qui est un langage interprété), la version en C++ est bien plus rapide que son homologue en Python. Le programme est également plus exportable. En effet, puisqu'il n'est plus interprété comme en Python, l'ordinateur executant le programme ne requière plus la présence d'une installation OpenCV. Le programme peut maitenant être distribué sur une simple clef USB.

Learn 'n' Recognize est distribué sous [licence Apache Version 2.0](http://www.apache.org/licenses/)