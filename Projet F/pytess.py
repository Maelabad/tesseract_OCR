

import sys 

def fonc(image):
    try:
        from PIL import Image
    except ImportError: 
        import images 
    import pytesseract

    #image = Image.open(image)
    #new_image = image.resize((1600, 2300))
    #new_image.save('Ntest6.jpg') 


    image = Image.open(image)
    image.thumbnail((2300, 1600))
    image.save('Ntest.jpg')

    mytext = open('Tempfile.txt','a')
    mytext.write(pytesseract.image_to_string(Image.open('Ntest.jpg')))
    #mytext.write(pytesseract.image_to_string(new_image))
    mytext.close()






print(fonc(sys.argv[1]))



