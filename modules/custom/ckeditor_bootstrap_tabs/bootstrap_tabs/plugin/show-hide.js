  var tabs = document.getElementsByClassName('tab-title');
  var clickTab = function(item) {
    console.log(item);
    var id = this.getAttribute('href');
    console.log(id);
    if (id.substring(0, 1) == '#') {
      id = id.substring(1);
    }
    var element = document.getElementById(id);
    console.log(element);
    toggleVisible(element);
  };

  Array.prototype.forEach.call(tabs, function(el) {
    el.addEventListener('click', clickTab, false);
  });




  var toggleVisible = function(item){
    if (item.style.display === 'none'){
      return item.style.display = 'block';
    }else{
      return item.style.display = 'none';
    }
  };

